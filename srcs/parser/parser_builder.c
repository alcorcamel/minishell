
#include "../../includes/parser.h"

t_ast	*ft_build_and_or(t_token **cur)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*tmp;
	t_token_type 	op;

	tmp = NULL;
	if (!cur || !(*cur))
		return NULL;
	left = ft_build_pipe(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOKEN_AND || (*cur)->type == TOKEN_OR))
	{
		op = (*cur)->type;
		*cur = (*cur)->next;
		right = ft_build_pipe(cur);
		if (!right)
			return (free_ast(&left), NULL);
		if (op == TOKEN_OR)
			tmp = ft_ast_new_bin(NODE_OR, left, right);
		else if (op == TOKEN_AND)
			tmp = ft_ast_new_bin(NODE_AND, left, right);
		if (!tmp)
			return (free_ast(&left), free_ast(&right), NULL);
		left = tmp;
	}
	return (left);
}

t_ast	*ft_build_pipe(t_token **cur)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*tmp;

	if (!cur || !(*cur))
		return NULL;
	left = ft_build_subshell(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOKEN_PIPE))
	{
		*cur = (*cur)->next;
		right = ft_build_subshell(cur);
		if (!right)
			return (free_ast(&left), NULL);
		tmp = ft_ast_new_bin(NODE_PIPE, left, right);
		if (!tmp)
			return (free_ast(&left), free_ast(&right), NULL);
		left = tmp;
	}
	return (left);
}

t_ast	*ft_build_subshell(t_token **cur)
{
	if (!cur || !*cur)
		return (NULL);
	if ((*cur)->type == TOKEN_LPAREN)
		return (ft_parse_subshell(cur));
	return (ft_parse_simple(cur));
}

t_ast	*ft_parse_subshell(t_token **cur)
{
	t_ast			*subshell;
	t_ast			*root;
	t_ast			*redir;
	t_ast			*redir_last;
	t_seg			*redir_arg;
	t_token_type	op;

	*cur = (*cur)->next;
	subshell = ft_build_and_or(cur);
	if (!subshell)
		return (NULL);
	redir_last = NULL;
	*cur = (*cur)->next;
	root = ft_ast_new_subshell(subshell);
	if (!root)
		return (free_ast(&subshell), NULL);
	while (*cur && ft_is_redir(*cur))
	{
		op = (*cur)->type;
		*cur = (*cur)->next;
		redir_arg = (*cur)->segs;
		(*cur)->segs = NULL;
		*cur = (*cur)->next;
		if (!redir_last)
			redir = ft_ast_new_redir(op, redir_arg, root);
		else
			redir = ft_ast_new_redir(op, redir_arg, redir_last->left);
		if (!redir)
			return (free_segs(redir_arg), free_ast(&root), NULL);
		if (redir_last)
			redir_last->left = redir;
		else
			root = redir;
		redir_last = redir;
	}
	return (root);
}

t_ast	*ft_parse_simple(t_token **cur)
{
	t_ast			*cmd;
	t_ast			*root;
	t_ast			*redir;
	t_ast			*redir_last;
	t_seg			*redir_arg;
	t_token_type	op;

	cmd = ft_ast_new_cmd(NULL);
	if (!cmd)
		return (NULL);
	redir_last = NULL;
	root = cmd;
	while (*cur && !ft_is_operator(*cur) && (*cur)->type != TOKEN_RPAREN
		&& (*cur)->type != TOKEN_LPAREN)
	{
		if ((*cur)->type == TOKEN_WORD)
		{
			if (!seg_append_words(&cmd->segs, (*cur)->segs))
				return (free_ast(&root), NULL);
			(*cur)->segs = NULL;
			*cur = (*cur)->next;
		}
		else if (ft_is_redir(*cur))
		{
			op = (*cur)->type;
			*cur = (*cur)->next;
			redir_arg = (*cur)->segs;
			(*cur)->segs = NULL;
			*cur = (*cur)->next;
			if (!redir_last)
				redir = ft_ast_new_redir(op, redir_arg, root);
			else
				redir = ft_ast_new_redir(op, redir_arg, redir_last->left);
			if (!redir)
				return (free_segs(redir_arg), free_ast(&root), NULL);
			if (redir_last)
				redir_last->left = redir;
			else
				root = redir;
			redir_last = redir;
		}
	}
	return (root);
}
