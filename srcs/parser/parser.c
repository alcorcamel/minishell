#include "../../includes/parser.h"

static int	ft_first_tok_checker(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (ft_pars_err(1, "|"), 0);
	else if (tok->type == TOKEN_OR)
		return (ft_pars_err(1, "||"), 0);
	else if (tok->type == TOKEN_AND)
		return (ft_pars_err(1, "&&"), 0);
	else if (tok->type == TOKEN_RPAREN)
		return (ft_pars_err(1, ")"), 0);
	return (1);
}

static int	ft_after_redir(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (ft_pars_err(1, "|"), 0);
	else if (tok->type == TOKEN_AND)
		return (ft_pars_err(1, "&&"), 0);
	else if (tok->type == TOKEN_OR)
		return (ft_pars_err(1, "||"), 0);
	else if (tok->type == TOKEN_RPAREN)
		return (ft_pars_err(1, ")"), 0);
	else if (tok->type == TOKEN_REDIR_IN)
		return (ft_pars_err(1, "<"), 0);
	else if (tok->type == TOKEN_REDIR_OUT)
		return (ft_pars_err(1, ">"), 0);
	else if (tok->type == TOKEN_APPEND)
		return (ft_pars_err(1, ">>"), 0);
	else if (tok->type == TOKEN_HEREDOC)
		return (ft_pars_err(1, "<<"), 0);
	return (1);
}

static int	ft_in_checker(t_token *tok, t_token_type prev)
{
	if (prev == TOKEN_REDIR_IN || prev == TOKEN_REDIR_OUT
		|| prev == TOKEN_HEREDOC || prev == TOKEN_APPEND)
		return (ft_after_redir(tok));
	else if (prev == TOKEN_PIPE || prev == TOKEN_AND
		|| prev == TOKEN_OR)
		return (ft_after_pipe(tok));
	else if (prev == TOKEN_LPAREN)
		return (ft_first_tok_checker(tok));
	else if (prev == TOKEN_RPAREN)
		return (ft_after_rparen(tok));
	return (1);
}

static int	ft_last_tok_checker(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (ft_pars_err(2, NULL), 0);
	if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT
		|| tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC
		|| tok->type == TOKEN_LPAREN)
		return (ft_pars_err(2, NULL), 0);
	return (1);
}

int	ft_parser(t_token *tokens)
{
	t_token			**tmp;
	t_token_type	prev;

	if (!tokens)
		return (0);
	tmp = &tokens;
	if (!ft_first_tok_checker(*tmp))
		return (free(tokens), 0);
	while ((*tmp)->next)
	{
		prev = (*tmp)->type;
		(*tmp) = (*tmp)->next;
		if (!ft_in_checker(*tmp, prev))
			return (free(tokens), 0);
	}
	if (ft_last_tok_checker(*tmp) == 0)
		return (free(tokens), 0);
	return (1);
}
