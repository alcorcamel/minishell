#include "executor.h"

int		ft_exec_pipe(t_ast *ast, t_shell *shell)
{
	int	pid[2];
	int	fd[2];
	int	pid_child;
	int	status_cmd;

	// a voir pendant la gestion des erreurs
	if (pipe(fd) < -1)
	{
		perror(ast->args[0]);
		return (-1);
	}
	shell->in_pipeline = TRUE;
	pid[0] = fork();
	if (pid[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		pid_child = ft_exec_ast(ast->left, shell);
		waitpid(pid_child, &status_cmd, 0);
		exit(WEXITSTATUS(status_cmd));
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		pid_child = ft_exec_ast(ast->left, shell);
		waitpid(pid_child, &status_cmd, 0);
		exit(WEXITSTATUS(status_cmd));
	}
	close(fd[0]);
	close(fd[1]);
}
