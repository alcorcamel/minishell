
#include "../includes/minishell.h"

static char	*ft_type_printer(t_token_type t)
{
	if (t == TOKEN_WORD)
		return ("WORD");
	if (t == TOKEN_PIPE)
		return ("PIPE");
	if (t == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (t == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (t == TOKEN_APPEND)
		return ("APPEND");
	if (t == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (t == TOKEN_LPAREN)
		return ("LBRACKET");
	if (t == TOKEN_RPAREN)
		return ("RBRACKET");
	return (NULL);
}

static void	ft_print_segs(t_seg *s)
{
	while (s)
	{
		if (s->type == SEG_RAW)
			printf(" RAW:%s", s->text);
		else if (s->type == SEG_SQ)
			printf(" SQ:%s", s->text);
		else if (s->type == SEG_DQ)
			printf(" DQ:%s", s->text);
		s = s->next;
	}
}

static void	ft_printer(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("noeud:%d %s", i, ft_type_printer(lst->type));
		if (lst->value)
			printf(" value=%s", lst->value);
		if (lst->segs)
			ft_print_segs(lst->segs);
		printf("\n");
		lst = lst->next;
		i++;
	}
}

static t_bool	ft_isinvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != 32)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_handle_lexer_error(char **line, t_shell *shell)
{
	if (errno == ENOMEM)
		shell->should_exit = 1;
	shell->last_status = 1;
	ft_free((void **)line);
	ft_verif_signal(shell);
	return (!shell->should_exit);
}

static int	ft_handle_script_lexer_error(char **line, t_shell *shell)
{
	if (errno == ENOMEM)
		shell->should_exit = 1;
	shell->last_status = 1;
	ft_free((void **)line);
	return (!shell->should_exit);
}

static void	ft_handle_ast_error(t_shell *shell)
{
	if (errno == ENOMEM)
		shell->should_exit = 1;
	shell->last_status = 1;
}

static void	ft_execute_ast(t_shell *shell)
{
	if (ft_explore_ast(&shell->root_ast, shell))
	{
		ft_ignore_signal_exec(shell);
		shell->last_status = ft_exec_ast(shell->root_ast, shell);
		ft_free_ast(&shell->root_ast);
	}
	else
	{
		if (shell->root_ast)
			ft_free_ast(&shell->root_ast);
		shell->last_status = 1;
	}
}

static void	ft_execute_tokens(t_token **tokens, t_token **head, t_shell *shell)
{
	if (ft_parser(*tokens))
	{
		shell->root_ast = ft_build_and_or(tokens);
		if (shell->root_ast)
		{
			ft_free_tokens(head);
			ft_execute_ast(shell);
		}
		else
			ft_handle_ast_error(shell);
	}
	else
	{
		ft_free_tokens(head);
		shell->last_status = 2;
	}
}

static void	ft_execute_script_ast(t_shell *shell)
{
	if (ft_explore_ast(&shell->root_ast, shell))
	{
		ft_ignore_signal_exec(shell);
		shell->last_status = ft_exec_ast(shell->root_ast, shell);
		ft_free_ast(&shell->root_ast);
	}
	else
	{
		if (shell->root_ast)
			ft_free_ast(&shell->root_ast);
		if (g_signal == SIGINT)
			shell->last_status = 130;
		else
			shell->last_status = 1;
	}
}

static void	ft_execute_script_tokens(t_token **tokens, t_token **head,
		t_shell *shell)
{
	if (ft_parser(*tokens))
	{
		shell->root_ast = ft_build_and_or(tokens);
		if (shell->root_ast)
		{
			ft_free_tokens(head);
			ft_execute_script_ast(shell);
		}
		else
		{
			if (errno == ENOMEM)
				shell->should_exit = 1;
			shell->last_status = 1;
		}
	}
	else
	{
		ft_free_tokens(head);
		shell->last_status = 2;
	}
}

static int	ft_process_line(char *line, t_shell *shell)
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

static int	ft_process_script_line(char **tmp, t_shell *shell)
{
	char	*line;
	t_token	*tokens;
	t_token	*head;

	line = ft_strtrim(*tmp, "\n");
	ft_free((void **)&(*tmp));
	ft_verif_signal(shell);
	ft_ignore_signal();
	if (!line)
		return (0);
	if (*line == '\0' || ft_isinvalid(line))
	{
		ft_free((void **)&line);
		shell->last_status = 0;
		return (1);
	}
	tokens = ft_lexer(line);
	if (!tokens)
		return (ft_handle_script_lexer_error(&line, shell));
	head = tokens;
	ft_execute_script_tokens(&tokens, &head, shell);
	ft_free((void **)&line);
	return (!shell->should_exit);
}

static void	ft_interactive_mode(t_shell *shell)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		ft_ignore_signal_prompt();
		line = readline("minishield~1.1> ");
		ft_verif_signal(shell);
		ft_ignore_signal();
		if (!line)
			break ;
		if (!ft_process_line(line, shell))
			break ;
	}
}

static int	ft_open_script_file(int ac, char **av)
{
	if (ac == 2)
		return (open(av[1], O_RDONLY));
	return (STDIN_FILENO);
}

static void	ft_script_mode(t_shell *shell, int ac, char **av)
{
	int		fd;
	char	*tmp;

	if (ac > 2)
	{
		ft_printf("minishield: too many arguments\n");
		exit(1);
	}
	fd = ft_open_script_file(ac, av);
	if (fd < 0)
		exit(1);
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (!ft_process_script_line(&tmp, shell))
			break ;
		tmp = get_next_line(fd);
	}
	get_next_line(-1000);
	if (fd != STDIN_FILENO)
		close(fd);
}

static void	ft_init_shell(t_shell *shell, char **envp, int ac)
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

static void	ft_cleanup_and_exit(t_shell *shell)
{
	t_shell	*p;

	clear_history();
	p = shell;
	ft_free_shell(&p);
	get_next_line(-1000);
	exit(shell->last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	ft_init_shell(&shell, envp, ac);
	if (shell.interactive && ac == 1)
		ft_interactive_mode(&shell);
	else
		ft_script_mode(&shell, ac, av);
	ft_cleanup_and_exit(&shell);
}
