#include "executor.h"
// pas gerer le cas pid == -1

int		ft_exec_subshell(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status_child;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status_child = ft_exec_ast(node->left, shell);
		exit(status_child);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
