/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:17:04 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:17:05 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	ft_add_op_helper2(t_token **lst, t_token *tok, char *s, int *i)
{
	if ((s[*i] == '>') && (s[*i + 1] == '|'))
	{
		tok = ft_toknew(TOKEN_REDIR_OUT);
		(*i)++;
	}
	else if (s[*i] == '|')
		tok = ft_toknew(TOKEN_PIPE);
	else if (s[*i] == '<')
		tok = ft_toknew(TOKEN_REDIR_IN);
	else if (s[*i] == '>')
		tok = ft_toknew(TOKEN_REDIR_OUT);
	else if (s[*i] == '(')
		tok = ft_toknew(TOKEN_LPAREN);
	else if (s[*i] == ')')
		tok = ft_toknew(TOKEN_RPAREN);
	else if (s[*i] == '&')
		return (ft_lex_err(12, "&"), 0);
	else
		return (0);
	if (!tok)
		return (0);
	return (ft_tokadd_back(lst, tok), (*i)++, 1);
}

static int	ft_add_op_helper3(t_token **lst, t_token *tok, int *i, char *s)
{
	if (s[*i] == '&' && s[*i + 1] == '&')
	{
		tok = ft_toknew(TOKEN_AND);
		if (!tok)
			return (0);
		ft_tokadd_back(lst, tok);
		(*i) += 2;
		return (1);
	}
	if (s[*i] == '|' && s[*i + 1] == '|')
	{
		tok = ft_toknew(TOKEN_OR);
		if (!tok)
			return (0);
		ft_tokadd_back(lst, tok);
		(*i) += 2;
		return (1);
	}
	return (2);
}

static int	ft_add_op_helper4(t_token **lst, t_token *tok, int *i, char *s)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		tok = ft_toknew(TOKEN_APPEND);
		if (!tok)
			return (0);
		ft_tokadd_back(lst, tok);
		(*i) += 2;
		return (1);
	}
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		tok = ft_toknew(TOKEN_HEREDOC);
		if (!tok)
			return (0);
		ft_tokadd_back(lst, tok);
		(*i) += 2;
		return (1);
	}
	return (2);
}

static int	ft_add_op_helper(t_token **lst, t_token *tok, char *s, int *i)
{
	int	k;

	if (s[*i] == '>' && s[*i + 1] == '<')
		return (ft_lex_err(12, "><"), 0);
	if (s[*i] == '<' && s[*i + 1] == '<' && s[*i + 2] == '<')
		return (ft_lex_err(11, "<"), 0);
	if (s[*i] == '>' && s[*i + 1] == '>' && s[*i + 2] == '>')
		return (ft_lex_err(11, ">"), 0);
	k = ft_add_op_helper3(lst, tok, i, s);
	if (k == 0)
		return (0);
	else if (k == 1)
		return (1);
	k = ft_add_op_helper4(lst, tok, i, s);
	if (k == 0)
		return (0);
	else if (k == 1)
		return (1);
	return (2);
}

int	ft_add_operator(t_token **lst, char *s, int *i, int *brace)
{
	t_token	*tok;
	int		ret;

	tok = NULL;
	if (s[*i] == '(')
		(*brace)++;
	if (s[*i] == ')')
	{
		(*brace)--;
		if (*brace < 0)
			return (ft_lex_err(12, ")"), 0);
	}
	if (s[*i] == ';')
		return (ft_lex_err(16, ";"), 0);
	if (s[*i] == '\\')
		return (ft_lex_err(16, "\\"), 0);
	ret = ft_add_op_helper(lst, tok, s, i);
	if (ret == 1)
		return (1);
	else if (ret == 0)
		return (0);
	if (ft_add_op_helper2(lst, tok, s, i) == 0)
		return (0);
	return (1);
}
