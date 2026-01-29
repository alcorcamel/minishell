
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

static void	ft_expand_and_rebuild_out(t_ast *node, t_shell *shell, int *fd)
{
	if (ft_redir_expand(node, shell) == 0 || ft_redir_rebuild(node) == 0)
	{
		ft_free_shell(&shell);
		exit(1);
	}
	*fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

int	ft_exec_redirect_in(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_throw_error("fork"));
	if (pid == 0)
	{
		ft_ignore_signal();
		ft_expand_and_rebuild_in(node, shell, &fd);
		if (fd == -1)
		{
			status = ft_throw_error(node->filename);
			ft_free_shell(&shell);
			exit(status);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		status = ft_exec_ast(node->left, shell);
		ft_free_shell(&shell);
		exit(status);
	}
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

int	ft_exec_redirect_out(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_throw_error("fork"));
	if (pid == 0)
	{
		ft_ignore_signal();
		ft_expand_and_rebuild_out(node, shell, &fd);
		if (fd == -1)
		{
			status = ft_throw_error(node->filename);
			ft_free_shell(&shell);
			exit(status);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		status = ft_exec_ast(node->left, shell);
		ft_free_shell(&shell);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
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
