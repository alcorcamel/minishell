
#include "../../includes/executor.h"

// pas gerer le cas de pid =-1 , status d exit a reveriifer

// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		status = ft_exec_ast(node, shell);
// 		exit(status);
// 	}
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	if (WIFSIGNALED(status))
// 		return (128 + WTERMSIG(status));
// 	return (0);
// }

int	ft_exec_cmd(t_ast *node, t_shell *shell)
{
	char	*path;
	pid_t	pid;
	int		status;
	char	**envp;
	// if (ft_is_builtin(node))
	// 	return (ft_exec_builtin(node, shell));
	if (ft_is_builtin(node, shell) == TRUE)
		return (ft_exec_built(node, shell));
	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		path = ft_get_path(node, shell);
		envp = ft_make_envp(shell->vars);
		if (!envp) // traiter avec l envp de secours
			exit(1);
		execve(path, node->args, envp);
		exit(ft_throw_error(path));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	// if (shell->in_pipeline == FALSE)
	// {
	// 	res = waitpid(pid, &status, 0);
	// 	if (WIFEXITED(status))
	// 		return (WEXITSTATUS(status));
	// 	if (WIFSIGNALED(status))
	// 		return (128 + WTERMSIG(status));
	// }
}
