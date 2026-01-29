
#include "../../includes/executor.h"

static void	ft_exit_err(t_shell *shell)
{
	ft_free_shell(&shell);
	exit(1);
}

static void	ft_free_all_after_cmd_err(char **path, char ***envp, t_shell *shell)
{
	ft_free_all_envp(envp);
	ft_free((void **)path);
	ft_free_shell(&shell);
}

static void	ft_exec_child(t_ast *node, t_shell *shell)
{
	char	*path;
	char	**envp;
	int		status;

	ft_restore_signal();
	if (ft_strlen(node->args[0]) == 0 && node->is_expanded)
	{
		ft_free_shell(&shell);
		exit(0);
	}
	path = ft_get_path(node, shell);
	if (!path)
	{
		status = ft_throw_error_cmd_not_found(node->args[0]);
		ft_free_shell(&shell);
		exit(status);
	}
	envp = ft_make_envp(shell->vars);
	if (!envp)
		ft_exit_err(shell);
	execve(path, node->args, envp);
	status = ft_throw_error_cmd(path);
	ft_free_all_after_cmd_err(&path, &envp, shell);
	exit(status);
}

int	ft_exec_cmd(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (ft_cmd_expand(node, shell) == 0 || ft_cmd_rebuild(node) == 0)
		return (1);
	if (!node->args || !node->args[0])
		return (0);
	if (ft_strncmp(node->args[0], "export", 7) == 0)
	{
		ft_free_args(node->args);
		node->args = NULL;
		if (ft_cmd_rebuild_noifs(node) == 0)
			return (1);
		if (!node->args || !node->args[0])
			return (0);
	}
	if (ft_is_builtin(node, shell) == TRUE)
		return (ft_exec_built(node, shell));
	pid = fork();
	if (pid == -1)
		return (ft_perror("fork"), 1);
	if (pid == 0)
		ft_exec_child(node, shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		if (status == 131)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		if (status == 130)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (status);
	}
	return (0);
}
