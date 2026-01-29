#include "../includes/minishell.h"

t_bool	ft_isinvalid(char *str)
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

int	ft_handle_lexer_error(char **line, t_shell *shell)
{
	if (errno == ENOMEM)
		shell->should_exit = 1;
	shell->last_status = 1;
	ft_free((void **)line);
	ft_verif_signal(shell);
	return (!shell->should_exit);
}

void	ft_handle_ast_error(t_shell *shell)
{
	if (errno == ENOMEM)
		shell->should_exit = 1;
	shell->last_status = 1;
}

void	ft_execute_ast(t_shell *shell)
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

void	ft_execute_tokens(t_token **tokens, t_token **head, t_shell *shell)
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
