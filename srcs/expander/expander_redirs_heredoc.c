/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirs_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 00:15:44 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 00:40:59 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static int	ft_handle_eof(int fd, int nb_lines, char *limiter, t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		ft_free_shell(&shell);
		close(fd);
		exit(130);
	}
	ft_printf_fd(STDERR_FILENO, "\nminishield: warning: here-document \
at line ");
	ft_printf_fd(STDERR_FILENO, "%d delimited by end-of-file (wanted `%s')\n",
		nb_lines, limiter);
	return (0);
}

int	ft_handle_heredoc_line(int fd, t_ast *n, int *nb_lines, t_shell *shell)
{
	char	*line;

	(*nb_lines)++;
	write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
		return (ft_handle_eof(fd, *nb_lines, n->limiter, shell));
	if (ft_is_limiter(line, n->limiter))
		return (free(line), 0);
	write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

void	ft_heredoc_child(t_ast *n, t_shell *shell)
{
	int		fd;
	int		nb_lines;
	int		ret;

	ft_restore_signal_heredoc();
	fd = open(n->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_free_shell(&shell);
		exit(1);
	}
	nb_lines = 0;
	while (1)
	{
		ret = ft_handle_heredoc_line(fd, n, &nb_lines, shell);
		if (ret == 0)
			break ;
		if (ret == 130)
			exit(130);
	}
	ft_free_shell(&shell);
	close(fd);
	exit(0);
}

int	ft_handle_exit_status(int status, t_ast *n)
{
	if (WEXITSTATUS(status) == 0)
		return (1);
	if (WEXITSTATUS(status) == 130)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_signal = SIGINT;
	}
	unlink(n->filename);
	return (0);
}

int	ft_wait_heredoc(pid_t pid, t_ast *n)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (ft_handle_exit_status(status, n));
	if (WIFSIGNALED(status))
	{
		unlink(n->filename);
		return (0);
	}
	return (1);
}
