#include "executor.h"

int		ft_exec_heredoc(t_ast *node, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status_child;
	char	*text;
	int		status;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		status_child = ft_exec_ast(node->left, shell);
		if (WIFEXITED(status_child))
			 exit(WEXITSTATUS(status_child));
		else if(WIFSIGNALED(status_child))
			exit(128 + WTERMSIG(status_child));
		exit(0);
	}
	text = NULL;
	signal(SIGINT, SIG_IGN);
	while ((text = readline("> ")) != NULL)
	{
		if (ft_strncmp(text, node->limiter, ft_strlen(node->limiter)) == 0)
			break;
		write(fd[1], text, ft_strlen(text));
		write(fd[1], '\n', 1);
		ft_free((void **)&text);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
