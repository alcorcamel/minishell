#include "../../includes/executor.h"

int		ft_exec_here_doc(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		fd;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_throw_error("fork"));
	if (pid == 0)
	{
		if (ft_heredoc_expand(node, shell))
			exit(1);
		fd = open(node->filename, O_RDONLY);
		if (fd == -1)
			return (ft_throw_error(node->filename));
		dup2(fd, STDIN_FILENO);
		unlink(node->filename);
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