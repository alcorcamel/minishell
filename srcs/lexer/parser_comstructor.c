/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_comstructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:32:24 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/11 22:43:26 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_ast *ast_new(t_node_type type)
{
	t_ast *n = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!n)
		return (NULL);
	n->type = type;
	return (n);
}

static t_ast *ast_new_binop(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast *n = ast_new(type);
	if (!n)
		return (NULL);
	n->left = left;
	n->right = right;
	return (n);
}

static t_ast *ast_new_cmd(t_seg *segs)
{
	t_ast *n = ast_new(NODE_CMD);
	if (!n)
		return (NULL);
	n->args = segs;
	return (n);
}

static t_ast *ast_new_subshell(t_ast *inside)
{
	t_ast *n = ast_new(NODE_SUBSHELL);
	if (!n)
		return (NULL);
	n->left = inside;
	return (n);
}
/* items a jouter ds la struct t_ast*/
static t_ast *ast_new_redir(t_token_type op, t_seg *lim, t_seg *filename, t_ast *left)
{
	t_ast *n;

	if (op == TOKEN_REDIR_IN)
		n = ast_new(NODE_REDIR_IN);
	else if (op == TOKEN_REDIR_OUT)
		n = ast_new(NODE_REDIR_OUT);
	else if (op == TOKEN_APPEND)
		n = ast_new(NODE_REDIR_APPEND);
	else
		n = ast_new(NODE_HEREDOC);
	if (!n)
		return (NULL);

	n->left = left;
	if (op == TOKEN_HEREDOC)
		n->limiter = segs;
	else
		n->filename = filename;
	return (n);
}

t_ast *build_and_or(t_token **cur)
{
	t_ast *left = build_pipe(cur);

	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		t_token_type op = (*cur)->type;
		*cur = (*cur)->next;
		t_ast *right = build_pipe(cur);
		left = new_bin(op == TOKEN_AND ? NODE_AND : NODE_OR, left, right);
	}
	return left;
}
