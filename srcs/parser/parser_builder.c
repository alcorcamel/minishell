#include "../../includes/parser.h"
#include "../../includes/expander.h"

int	ft_build_and_or2(t_token **cur, t_ast **left, t_token_type op, t_ast *tmp)
{
	t_ast	*right;

	op = (*cur)->type;
	*cur = (*cur)->next;
	right = ft_build_pipe(cur);
	if (!right)
		return (ft_free_ast(left), 0);
	if (op == TOKEN_OR)
		tmp = ft_ast_new_bin(NODE_OR, *left, right);
	else if (op == TOKEN_AND)
		tmp = ft_ast_new_bin(NODE_AND, *left, right);
	if (!tmp)
		return (ft_free_ast(left), ft_free_ast(&right), 0);
	*left = tmp;
	return (1);
}

t_ast	*ft_build_and_or(t_token **cur)
{
	t_ast			*left;
	t_ast			*tmp;
	t_token_type	op;

	tmp = NULL;
	op = TOKEN_AND;
	if (!cur || !(*cur))
		return (NULL);
	left = ft_build_pipe(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		if (!ft_build_and_or2(cur, &left, op, tmp))
			return (NULL);
	}
	return (left);
}

t_ast	*ft_build_pipe(t_token **cur)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*tmp;

	if (!cur || !(*cur))
		return (NULL);
	left = ft_build_subshell(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOKEN_PIPE))
	{
		*cur = (*cur)->next;
		right = ft_build_subshell(cur);
		if (!right)
			return (ft_free_ast(&left), NULL);
		tmp = ft_ast_new_bin(NODE_PIPE, left, right);
		if (!tmp)
			return (ft_free_ast(&left), ft_free_ast(&right), NULL);
		left = tmp;
	}
	return (left);
}

int	ft_subsh2(t_token **cur, t_ast **root, t_token_type *op, t_ast **r_last)
{
	t_ast			*redir;
	t_seg			*redir_arg;

	*op = (*cur)->type;
	*cur = (*cur)->next;
	redir_arg = (*cur)->segs;
	(*cur)->segs = NULL;
	*cur = (*cur)->next;
	if (!(*r_last))
		redir = ft_ast_new_redir(*op, redir_arg, *root);
	else
		redir = ft_ast_new_redir(*op, redir_arg, (*r_last)->left);
	if (!redir)
		return (free_segs(redir_arg), ft_free_ast(root), 0);
	if (*r_last)
		(*r_last)->left = redir;
	else
		*root = redir;
	*r_last = redir;
	return (1);
}

t_ast	*ft_parse_subshell(t_token **cur)
{
	t_ast			*subshell;
	t_ast			*root;
	t_ast			*redir_last;
	t_token_type	op;

	*cur = (*cur)->next;
	subshell = ft_build_and_or(cur);
	if (!subshell)
		return (NULL);
	redir_last = NULL;
	*cur = (*cur)->next;
	root = ft_ast_new_subshell(subshell);
	if (!root)
		return (ft_free_ast(&subshell), NULL);
	while (*cur && ft_is_redir(*cur))
	{
		if (!ft_subsh2(cur, &root, &op, &redir_last))
			return (NULL);
	}
	return (root);
}
