#include "executor.h"

// pas gerer le cas de pid =-1 , status d exit a reveriifer

int	ft_exec_cmd(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		res;

	// if (ft_is_builtin(node))
	// 	return (ft_exec_builtin(node, shell));
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(node->args[0], node->args, shell->envp);
		perror(node->args[0]);
		exit(127);
	}
	if (shell->in_pipeline == FALSE)
	{
		res = waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (pid);
}
