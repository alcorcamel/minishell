
#include "lexer.h"

static void free_segs(t_seg *s)
{
	t_seg *next;
	while (s)
	{
		next = s->next;
		free(s->text);
		free(s);
		s = next;
	}
}

static void	free_ast(t_ast **root)
{
	t_ast	*n;

	if (!root || !*root)
		return;

	n = *root;
	if (n->left)
		free_ast(&n->left);
	if (n->right)
		free_ast(&n->right);
	free_segs(n->segs);
	// fonction pour free les alloc ds chaque noeud!!
	free(n);
	*root = NULL;
}

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
	t_ast	*n = ft_ast_new(type);

	if (!n)
		return (NULL);
	n->left = left;
	n->right = right;
	return (n);
}

static t_ast *ft_ast_new_cmd(t_seg *segs)
{
	t_ast	*n = ft_ast_new(NODE_CMD);

	if (!n)
		return (NULL);
	n->segs = segs;
	return (n);
}

static t_ast *ft_ast_new_subshell(t_ast *inside)
{
	t_ast	*n = ft_ast_new(NODE_SUBSHELL);

	if (!n)
		return (NULL);
	n->left = inside;
	return (n);
}

static int	ft_is_op(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_OR || op == TOKEN_AND || op == TOKEN_PIPE
		|| op == TOKEN_RPAREN || op == TOKEN_REDIR_IN
		|| op == TOKEN_REDIR_OUT || op == TOKEN_APPEND
		|| op == TOKEN_HEREDOC || op == TOKEN_LPAREN)
		return (1);
	return (0);
}

static t_ast *ft_ast_new_redir(t_token_type op, t_seg *segs, t_ast *left)
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

static int	ft_is_redir(t_token *cur)
{
	if (!cur)
		return (0);
	if (cur->type == TOKEN_REDIR_IN || cur->type == TOKEN_REDIR_OUT
		|| cur->type == TOKEN_APPEND || cur->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

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
	t_ast	*left;
	t_ast	*right;

}
