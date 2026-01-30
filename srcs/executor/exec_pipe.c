/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:05 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 02:10:23 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	ft_close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	ft_exec_child(int fd[2], t_ast *node_child, t_shell *shell,
	int child)
{
	int	status;
	int	dup_fd;
	int	index_fd;

	if (child == 1)
	{
		index_fd = 1;
		dup_fd = STDOUT_FILENO;
	}
	if (child == 2)
	{
		index_fd = 0;
		dup_fd = STDIN_FILENO;
	}
	ft_ignore_signal();
	if (dup2(fd[index_fd], dup_fd) < 0)
	{
		ft_close_fd(fd);
		ft_free_shell(&shell);
		exit(ft_throw_error("dup2"));
	}
	ft_close_fd(fd);
	status = ft_exec_ast(node_child, shell);
	ft_free_shell(&shell);
	exit(status);
}

static int	ft_recup_status(int pid[2])
{
	int		i;
	pid_t	pid_check;
	int		status[2];
	int		last_status;

	i = -1;
	last_status = 0;
	while (++i < 2)
	{
		pid_check = wait(&status[i]);
		if (pid_check == pid[1])
			last_status = status[i];
	}
	return (last_status);
}

int	ft_exec_pipe(t_ast *ast, t_shell *shell)
{
	pid_t	pid[2];
	int		fd[2];
	int		last_status;

	if (pipe(fd) == -1)
		return (ft_throw_error("pipe"));
	pid[0] = fork();
	if (pid[0] == -1)
		return (ft_throw_error("fork"));
	if (pid[0] == 0)
		ft_exec_child(fd, ast->left, shell, 1);
	pid[1] = fork();
	if (pid[1] == -1)
		return (ft_throw_error("fork"));
	if (pid[1] == 0)
		ft_exec_child(fd, ast->right, shell, 2);
	ft_close_fd(fd);
	last_status = ft_recup_status(pid);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (0);
}
