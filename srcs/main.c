
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_ast	*root;
	t_shell	shell;
	char	*prompt;
	int		res;

	shell.vars = NULL;
	shell.last_status = 0;
	if (ft_cpy_enpv(envp, &shell) == FALSE)
		exit(1);
	while (1)
	{
		ft_ignore_signal_prompt();
		prompt = ft_generate_prompt(&shell);
		line = readline(prompt);
		ft_free((void **)&prompt);
		if (!line)
			return (1);
		ft_verif_signal(&shell);
		if (*line == '\0')
		{
			ft_free((void **)&line);
			continue ;
		}
		ft_ignore_signal_exec();
		tokens = ft_lexer(line);
		add_history (line);
		ft_parser(tokens);
		root = ft_build_and_or(&tokens);
		ft_explore_ast(&root, &shell);
		shell.last_status = ft_exec_ast(root, &shell);
		ft_free((void **)&line);
		ft_verif_signal(&shell);
	}
	return (0);
}
