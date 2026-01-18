#include "../../includes/parser.h"

int	ft_parsimpl2(t_token **cur, t_ast **root, t_token_type *op, t_ast **r_last)
{
	t_seg	*redir_arg;
	t_ast	*redir;

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
		return (free_segs(redir_arg), free_ast(root), 0);
	if (*r_last)
		(*r_last)->left = redir;
	else
		*root = redir;
	*r_last = redir;
	return (1);
}

static int	ft_parse_simple3(t_ast **cmd, t_ast **root, t_token **cur)
{
	if (!seg_append_words(&(*cmd)->segs, (*cur)->segs))
		return (free_ast(root), 0);
	(*cur)->segs = NULL;
	*cur = (*cur)->next;
	return (1);
}

t_ast	*ft_parse_simple(t_token **cur)
{
	t_ast			*cmd;
	t_ast			*root;
	t_ast			*redir_last;
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
			if (!ft_parse_simple3(&cmd, &root, cur))
				return (NULL);
		}
		else if (ft_is_redir(*cur))
		{
			if (!ft_parsimpl2(cur, &root, &op, &redir_last))
				return (NULL);
		}
	}
	return (root);
}

t_ast	*ft_build_subshell(t_token **cur)
{
	if (!cur || !*cur)
		return (NULL);
	if ((*cur)->type == TOKEN_LPAREN)
		return (ft_parse_subshell(cur));
	return (ft_parse_simple(cur));
}
