
#include "../../includes/executor.h"

// pas gerer le cas de pid =-1 , status d exit a reveriifer

int	ft_exec_cmd(t_ast *node, t_shell *shell)
{
	char	*path;
	pid_t	pid;
	int		status;
	char	**envp;

	if (ft_cmd_expand(node, shell) == 0)
		return (1);
	if (ft_cmd_rebuild(node) == 0)
		return (1);
	if (ft_is_builtin(node, shell) == TRUE)
		return (ft_exec_built(node, shell));
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		path = ft_get_path(node, shell);
		if (!path)
			exit(ft_throw_error(node->args[0]));
		envp = ft_make_envp(shell->vars);
		if (!envp) // traiter avec l envp de secours
			exit(1);
		execve(path, node->args, envp);
		exit(ft_throw_error(path));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
}
