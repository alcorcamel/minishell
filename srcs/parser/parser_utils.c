#include "../../includes/parser.h"

int	ft_is_operator(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_OR || op == TOKEN_AND || op == TOKEN_PIPE)
		return (1);
	return (0);
}

int	ft_is_paren(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_RPAREN || op == TOKEN_LPAREN)
		return (1);
	return (0);
}

int	ft_is_redir(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_REDIR_IN || op == TOKEN_REDIR_OUT
		|| op == TOKEN_APPEND || op == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	ft_after_rparen(t_token *tok)
{
	if (tok->type == TOKEN_WORD)
		return (ft_pars_err(1, tok->value), 0);
	else if (tok->type == TOKEN_LPAREN)
		return (ft_pars_err(1, "("), 0);
	return (1);
}

int	ft_after_pipe(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (ft_pars_err(1, "|"), 0);
	else if (tok->type == TOKEN_AND)
		return (ft_pars_err(1, "&&"), 0);
	else if (tok->type == TOKEN_OR)
		return (ft_pars_err(1, "||"), 0);
	else if (tok->type == TOKEN_RPAREN)
		return (ft_pars_err(1, ")"), 0);
	return (1);
}
