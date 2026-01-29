#include "../includes/minishell.h"

int	ft_process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_token	*head;

	if (*line == '\0' || ft_isinvalid(line))
	{
		ft_free((void **)&line);
		shell->last_status = 0;
		return (1);
	}
	tokens = ft_lexer(line);
	if (!tokens)
		return (ft_handle_lexer_error(&line, shell));
	head = tokens;
	add_history(line);
	ft_execute_tokens(&tokens, &head, shell);
	ft_free((void **)&line);
	ft_verif_signal(shell);
	return (!shell->should_exit);
}

void	ft_interactive_mode(t_shell *shell)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		ft_ignore_signal_prompt();
		line = readline("minishield-1.0$ ");
		ft_verif_signal(shell);
		ft_ignore_signal();
		if (!line)
			break ;
		if (!ft_process_line(line, shell))
			break ;
	}
}

void	ft_init_shell(t_shell *shell, char **envp)
{
	shell->vars = NULL;
	shell->last_status = 0;
	shell->should_exit = 0;
	shell->root_ast = NULL;
	shell->prompt = NULL;
	shell->interactive = 0;
	g_signal = 0;
	if (ft_cpy_enpv(envp, shell) == FALSE)
		exit(1);
	shell->interactive = isatty(STDIN_FILENO);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_cleanup_and_exit(t_shell *shell)
{
	t_shell	*p;

	clear_history();
	p = shell;
	ft_free_shell(&p);
	get_next_line(-1000);
	exit(shell->last_status);
}

int	ft_process_minishell(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	ft_init_shell(&shell, envp);
	if (shell.interactive && ac == 1)
		ft_interactive_mode(&shell);
	else
		printf("Not implement for not required in sujet\n");
	ft_cleanup_and_exit(&shell);
	return (0);
}
