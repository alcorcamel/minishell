/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:08 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 00:43:28 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	ft_expand_and_rebuild_in(t_ast *node, t_shell *shell, int *fd)
{
	if (ft_redir_expand(node, shell) == 0 || ft_redir_rebuild(node) == 0)
	{
		ft_free_shell(&shell);
		exit(1);
	}
	*fd = open(node->filename, O_RDONLY);
}

static void	ft_exec_child_redirect_in(t_ast *node, t_shell *shell)
{
	int	fd;
	int	status;

	ft_ignore_signal();
	ft_expand_and_rebuild_in(node, shell, &fd);
	if (fd == -1)
	{
		status = ft_throw_error(node->filename);
		ft_free_shell(&shell);
		exit(status);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_free_shell(&shell);
		close(fd);
		exit(1);
	}
	close(fd);
	status = ft_exec_ast(node->left, shell);
	ft_free_shell(&shell);
	exit(status);
}

int	ft_exec_redirect_in(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_throw_error("fork"));
	if (pid == 0)
		ft_exec_child_redirect_in(node, shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 126)
			return (1);
		else
			return (WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
