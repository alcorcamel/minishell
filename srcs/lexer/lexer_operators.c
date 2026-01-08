/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 22:04:53 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/07 22:57:49 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_remi.h"

/*pour || et && a ajouter pour le bonus*/

static int	ft_add_op_helper(t_token **lst, t_token *tok, char *s, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		tok = ft_toknew(TOKEN_HEREDOC);
		if (!tok)
			return (0);
		ft_tokadd_back(lst, tok);
		(*i) += 2;
		return (1);
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		tok = ft_toknew(TOKEN_APPEND);
		if (!tok)
			return (0);
		ft_tokadd_back(lst, tok);
		(*i) += 2;
		return (1);
	}
	return (0);
}

int	ft_add_operator(t_token **lst, char *s, int *i)
{
	t_token	*tok;
	if (s[*i] == '|' && s[*i + 1] == '|')
		return (0);//erreur pour mandatory
	if (s[*i] == '&' && s[*i + 1] == '&')
		return (0);//erreur pour mandatory
	if (ft_add_op_helper(lst, tok, s, i) == 1)
		return (1);
	if (s[*i] == '|')
		tok = ft_toknew(TOKEN_PIPE);
	else if (s[*i] == '<')
		tok = ft_toknew(TOKEN_REDIR_IN);
	else if (s[*i] == '>')
		tok = ft_toknew(TOKEN_REDIR_OUT);
	else if (s[*i] == '(')
		tok = ft_toknew(TOKEN_LBRACKET);
	else if (s[*i] == ')')
		tok = ft_toknew(TOKEN_RBRACKET);
	else if (s[*i] == '&')
		return (0);//erreur pour mandatory
	else
		return (0);
	if (!tok)
		return (0);
	return (ft_tokadd_back(lst, tok), (*i)++, 1);
}
