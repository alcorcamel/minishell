
#include "../../includes/executor.h"

//manque a gerer les erreurs de open et de dup2 au cas ou ca foire

int		ft_exec_redirect_in(t_ast *node, t_shell *shell)
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
		fd = open(node->filename, O_RDONLY);
		if (fd == -1)
			return (ft_throw_error(node->filename));
		dup2(fd, STDIN_FILENO);
		close(fd);
		status = ft_exec_ast(node->left, shell);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int		ft_exec_redirect_out(t_ast *node, t_shell *shell)
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
		fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_throw_error(node->filename));
		dup2(fd, STDOUT_FILENO);
		close(fd);
		status = ft_exec_ast(node->left, shell);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
