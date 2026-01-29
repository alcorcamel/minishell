/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:22 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:19:22 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_ast	*ft_ast_new(t_node_type type)
{
	t_ast	*n;

	n = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!n)
		return (NULL);
	n->type = type;
	return (n);
}

t_ast	*ft_ast_new_bin(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*n;

	n = ft_ast_new(type);
	if (!n)
		return (NULL);
	n->left = left;
	n->right = right;
	return (n);
}

t_ast	*ft_ast_new_cmd(t_seg *segs)
{
	t_ast	*n;

	n = ft_ast_new(NODE_CMD);
	if (!n)
		return (NULL);
	n->segs = segs;
	return (n);
}

t_ast	*ft_ast_new_subshell(t_ast *subshell)
{
	t_ast	*n;

	n = ft_ast_new(NODE_SUBSHELL);
	if (!n)
		return (NULL);
	n->left = subshell;
	return (n);
}

t_ast	*ft_ast_new_redir(t_token_type op, t_seg *segs, t_ast *left)
{
	t_ast	*n;

	if (op == TOKEN_REDIR_IN)
		n = ft_ast_new(NODE_REDIR_IN);
	else if (op == TOKEN_REDIR_OUT)
		n = ft_ast_new(NODE_REDIR_OUT);
	else if (op == TOKEN_APPEND)
		n = ft_ast_new(NODE_REDIR_APPEND);
	else if (op == TOKEN_HEREDOC)
		n = ft_ast_new(NODE_HEREDOC);
	else
		return (NULL);
	if (!n)
		return (NULL);
	n->left = left;
	n->segs = segs;
	return (n);
}
