
#include "../../includes/executor.h"

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
		fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
