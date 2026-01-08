#include "executor.h"

int		ft_exec_pipe(t_ast *ast, t_shell *shell)
{
	pid_t	pid[2];
	int		fd[2];
	pid_t	pid_child;
	int		status_cmd;
	pid_t	pid_waited;
	int		status[2];
	int		last_status;
	// a voir pendant la gestion des erreurs je sais pas encore comment gerer les erreurs pour le moment
	if (pipe(fd) == -1)
	{
		perror(ast->args[0]);
		return (-1);
	}
	shell->in_pipeline = TRUE;
	pid[0] = fork();
	if (pid[0] == -1)
	{
		perror(ast->args[0]);
		return (-1);
	}
	if (pid[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		pid_child = ft_exec_ast(ast->left, shell);
		waitpid(pid_child, &status_cmd, 0);
		if(WIFEXITED(status_cmd))
			exit(WEXITSTATUS(status_cmd));
		if (WIFSIGNALED(status_cmd))
			exit(128 + WTERMSIG(status_cmd));
		exit(0);
	}
	pid[1] = fork();
	if (pid[1] == -1)
	{
		perror(ast->args[0]);
		return (-1);
	}
	if (pid[1] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		pid_child = ft_exec_ast(ast->right, shell);
		waitpid(pid_child, &status_cmd, 0);
		if(WIFEXITED(status_cmd))
			exit(WEXITSTATUS(status_cmd));
		if (WIFSIGNALED(status_cmd))
			exit(128 + WTERMSIG(status_cmd));
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	shell->in_pipeline = FALSE;
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	last_status = status[1];
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (0);
}
