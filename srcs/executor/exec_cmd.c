#include "executor.h"

// pas gerer le cas de pid =-1 , status d exit a reveriifer

int	ft_exec_cmd(t_ast *node, t_shell *shell)
{
	char	*path;
	// if (ft_is_builtin(node))
	// 	return (ft_exec_builtin(node, shell));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = ft_get_path(node, shell);
	execve(path, node->args, shell->envp);
	perror(path);
	exit(127);
	return (0);
	// if (shell->in_pipeline == FALSE)
	// {
	// 	res = waitpid(pid, &status, 0);
	// 	if (WIFEXITED(status))
	// 		return (WEXITSTATUS(status));
	// 	if (WIFSIGNALED(status))
	// 		return (128 + WTERMSIG(status));
	// }
}
