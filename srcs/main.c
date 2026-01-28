
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

int main(int ac, char **av, char **envp)
{
	char	*line;
	char	*tmp;
	t_token	*tokens;
	t_token	*head;
	t_shell	shell;
	t_shell	*p;
	int		fd;

	(void)av;
	shell.vars = NULL;
	shell.last_status = 0;
	shell.should_exit = 0;
	shell.root_ast = NULL;
	shell.vars = NULL;
	shell.prompt = NULL;
	shell.last_status = 0;
	if (ft_cpy_enpv(envp, &shell) == FALSE)
		exit(1);
	shell.interactive = isatty(STDIN_FILENO);
	if (shell.interactive && ac == 1)
	{
		while (1)
		{
			ft_ignore_signal_prompt();
			shell.prompt = ft_generate_prompt(&shell);
			line = readline(shell.prompt);
			ft_free((void **)&shell.prompt);

			ft_verif_signal(&shell);
			ft_ignore_signal();

			if (!line)
				break ;

			if (*line == '\0')
			{
				ft_free((void **)&line);
				shell.last_status = 0;
				continue ;
			}

			tokens = ft_lexer(line);
			if (!tokens)
			{
				if (errno == 12)
					shell.should_exit = 1;
				shell.last_status = 1;
			}
			else
			{
				head = tokens;
				add_history(line);

				if (ft_parser(tokens))
				{
					shell.root_ast = ft_build_and_or(&tokens);
					if (shell.root_ast)
					{
						ft_free_tokens(&head);
						if (ft_explore_ast(&shell.root_ast, &shell))
						{
							ft_ignore_signal_exec(&shell);
							shell.last_status = ft_exec_ast(shell.root_ast, &shell);
							ft_free_ast(&shell.root_ast);
						}
						else
						{
							if (shell.root_ast)
								ft_free_ast(&shell.root_ast);
							shell.last_status = 1;
						}
					}
					else
					{
						if (errno == 12)
							shell.should_exit = 1;
						shell.last_status = 1;
					}
				}
				else
				{
					ft_free_tokens(&head);
					shell.last_status = 2;
				}
			}
			ft_free((void **)&line);
			ft_verif_signal(&shell);

			if (shell.should_exit)
				break ;
		}
	}
	else
	{
		if (ac > 2)
		{
			ft_printf("minishield: too many arguments\n");
			exit(1);
		}

		if (ac == 2)
			fd = open(av[1], O_RDONLY);
		else
			fd = STDIN_FILENO;

		if (fd < 0)
			exit(1);

		tmp = get_next_line(fd);
		while (tmp)
		{
			line = ft_strtrim(tmp, "\n");
			ft_free((void **)&tmp);

			ft_verif_signal(&shell);
			ft_ignore_signal();

			if (!line)
				break ;

			if (*line == '\0')
			{
				ft_free((void **)&line);
				shell.last_status = 0;
				tmp = get_next_line(fd);
				continue ;
			}

			tokens = ft_lexer(line);
			if (!tokens)
			{
				if (errno == 12)
					shell.should_exit = 1;
				shell.last_status = 1;
			}
			head = tokens;

			if (ft_parser(tokens))
			{
				shell.root_ast = ft_build_and_or(&tokens);
				if (shell.root_ast)
				{
					ft_free_tokens(&head);
					if (ft_explore_ast(&shell.root_ast, &shell))
					{
						ft_ignore_signal_exec(&shell);
						shell.last_status = ft_exec_ast(shell.root_ast, &shell);
						ft_free_ast(&shell.root_ast);
					}
					else
					{
						if (shell.root_ast)
							ft_free_ast(&shell.root_ast);
						shell.last_status = 1;
					}
				}
				else
				{
					if (errno == 12)
						shell.should_exit = 1;
					shell.last_status = 1;
				}

			}
			else
			{
				ft_free_tokens(&head);
				shell.last_status = 2;
			}

			ft_free((void **)&line);

			if (shell.should_exit)
				break ;

			tmp = get_next_line(fd);
		}

		if (fd != STDIN_FILENO)
			close(fd);
	}
	clear_history();
	p = &shell;
	ft_free_shell(&p);
	exit(shell.last_status);
}

