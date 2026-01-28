
#include "../../includes/executor.h"

static void	ft_expand_and_rebuild_append(t_ast *node, t_shell *shell, int *fd)
{
	if (ft_redir_expand(node, shell) == 0 || ft_redir_rebuild(node) == 0)
	{
		ft_free_shell(&shell);
		exit(1);
	}
	*fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	ft_exec_append(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_throw_error("fork"));
	if (pid == 0)
	{
		ft_restore_signal();
		ft_expand_and_rebuild_append(node, shell, &fd);
		if (fd == -1)
			return (ft_throw_error(node->filename));
		dup2(fd, STDOUT_FILENO);
		close(fd);
		status = ft_exec_ast(node->left, shell);
		ft_free_shell(&shell);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
