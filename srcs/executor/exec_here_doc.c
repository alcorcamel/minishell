/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 02:45:53 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	ft_exec_child(t_shell *shell, t_ast *node)
{
	int	fd;
	int	status;

	ft_ignore_signal();
	if (ft_heredoc_expand(node, shell) == 0)
	{
		ft_free_shell(&shell);
		exit(1);
	}
	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
		return (ft_free_shell(&shell), exit(ft_throw_error("open")));
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		ft_free_shell(&shell);
		exit(1);
	}
	if (unlink(node->filename) == -1)
		return (ft_free_shell(&shell), exit(ft_throw_error("unlink")));
	close(fd);
	status = ft_exec_ast(node->left, shell);
	ft_free_shell(&shell);
	exit(status);
}

int	ft_exec_here_doc(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_throw_error("fork"));
	if (pid == 0)
		ft_exec_child(shell, node);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
