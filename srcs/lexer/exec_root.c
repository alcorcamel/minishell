
#include "lexer.h"

// a mettre avant d executer cette fonction
// signal(SIGNINT, SIG_IGN)
// permet d ignorer le signal dans le process parent
// on le restaura dans les differentes commandes

int	ft_exec_root(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status = ft_exec_ast(node, shell);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
