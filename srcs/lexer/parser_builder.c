
#include "lexer.h"

static t_ast *ft_ast_new(t_node_type type)
{
	t_ast	*n = (t_ast *)ft_calloc(1, sizeof(t_ast));

	if (!n)
		return (NULL);
	n->type = type;
	return (n);
}

static t_ast *ft_ast_new_bin(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*n = ast_new(type);

	if (!n)
		return (NULL);
	n->left = left;
	n->right = right;
	return (n);
}

static t_ast *ft_ast_new_cmd(t_seg *segs)
{
	t_ast	*n = ast_new(NODE_CMD);

	if (!n)
		return (NULL);
	n->args = segs;
	return (n);
}

static t_ast *ft_ast_new_subshell(t_ast *inside)
{
	t_ast	*n = ast_new(NODE_SUBSHELL);

	if (!n)
		return (NULL);
	n->left = inside;
	return (n);
}

static int	ft_is_op(t_token **cur)
{
	t_token_type	op;

	op = (*cur)->type;
	if (op == TOKEN_OR || op == TOKEN_AND || op == TOKEN_PIPE)
		return (1);
	return (0);
}

static t_ast *ft_ast_new_redir(t_token_type op, t_seg *segs, t_ast *left)
{
	t_ast	*n;

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
	n->segs = segs;
	return (n);
}

static int	ft_is_redir(t_token **cur)
{
	if ((*cur)->type == TOKEN_REDIR_IN || (*cur)->type == TOKEN_REDIR_OUT
		|| (*cur)->type == TOKEN_APPEND || (*cur)->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

t_ast	*ft_build_and_or(t_token **cur)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	op;

	left = build_pipe(cur);
	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		op = (*cur)->type;
		*cur = (*cur)->next;
		right = build_pipe(cur);
		left = new_bin(op, left, right);
	}
	return (left);
}

t_ast	*ft_build_pipe(t_token **cur)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	op;

	left = build_subshell(cur);
	while (*cur && ((*cur)->type == TOKEN_PIPE))
	{
		op = (*cur)->type;
		*cur = (*cur)->next;
		right = build_subshell(cur);
		left = new_bin(op, left, right);
	}
	return (left);
}

int	ft_lbracket_checker(t_token **cur)
{
	t_token	*tmp;

	tmp = (*cur);
	while (!ft_is_op(&tmp))
	{
		if (tmp->type == TOKEN_LBRACKET)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_ast	*ft_build_subshell(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	if (ft_lbracket_checker(cur))
		ft_simple_parser(cur);
	else
	{
		if (ft_is_redir(cur))





	}
}
