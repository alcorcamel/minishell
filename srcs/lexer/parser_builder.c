
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

static t_seg	*seg_last(t_seg *s)
{
	if (!s)
		return (NULL);
	while (s->next)
		s = s->next;
	return (s);
}

static void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;
	size_t	total_size;

	total_size = elementCount * elementSize;
	if (elementSize && total_size / elementSize != elementCount)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

static int	seg_append_words(t_seg **dst, t_seg *src)
{
	t_seg	*last;

	if (!src)
		return (1);
	if (!dst)
		return (0);
	if (!*dst)
		return (*dst = src, 1);
	last = seg_last(*dst);
	last->next = src;
	return (1);
}

static t_seg	*seg_word_separator(void)
{
	t_seg	*sep;

	sep = (t_seg *)ft_calloc(1, sizeof(t_seg));
	if (!sep)
		return (NULL);
	sep->type = SEG_SEP;
	sep->text = (char *)ft_calloc(1, sizeof(char));
	if (!sep->text)
		return (free(sep), NULL);
	sep->next = NULL;
	return (sep);
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

static t_ast *ft_ast_new_subshell(t_ast *subshell)
{
	t_ast	*n = ft_ast_new(NODE_SUBSHELL);

	if (!n)
		return (NULL);
	n->left = subshell;
	return (n);
}

static int	ft_is_operator(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_OR || op == TOKEN_AND || op == TOKEN_PIPE)
		return (1);
	return (0);
}

static int	ft_is_paren(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_RPAREN || op == TOKEN_LPAREN)
		return (1);
	return (0);
}

static int	ft_is_redir(t_token *cur)
{
	t_token_type	op;

	if (!cur)
		return (0);
	op = cur->type;
	if (op == TOKEN_REDIR_IN || op == TOKEN_REDIR_OUT
		|| op == TOKEN_APPEND || op == TOKEN_HEREDOC)
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
	t_seg			*redir_arg;
	t_token_type	op;

	*cur = (*cur)->next;
	subshell = ft_build_and_or(cur);
	if (!subshell)
		return (NULL);
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
		redir = ft_ast_new_redir(op, redir_arg, root);
		if (!redir)
			return (free_segs(redir_arg), free_ast(&root), NULL);
		root = redir;
	}
	return (root);
}

t_ast	*ft_parse_simple(t_token **cur)
{
	t_ast			*cmd;
	t_ast			*root;
	t_ast			*redir;
	t_seg			*sep;
	t_seg			*redir_arg;
	t_token_type	op;

	cmd = ft_ast_new_cmd(NULL);
	if (!cmd)
		return (NULL);
	root = cmd;
	while (*cur && !ft_is_operator(*cur) && (*cur)->type != TOKEN_RPAREN
		&& (*cur)->type != TOKEN_LPAREN)
	{
		if ((*cur)->type == TOKEN_WORD)
		{
			if (!seg_append_words(&cmd->segs, (*cur)->segs))
				return (free_ast(&root), NULL);
			(*cur)->segs = NULL;
			sep = seg_word_separator();
			if (!sep)
				return (free_ast(&root), NULL);
			if (!seg_append_words(&cmd->segs, sep))
				return (free_segs(sep), free_ast(&root), NULL);
			*cur = (*cur)->next;
		}
		else if (ft_is_redir(*cur))
		{
			op = (*cur)->type;
			*cur = (*cur)->next;
			redir_arg = (*cur)->segs;
			(*cur)->segs = NULL;
			*cur = (*cur)->next;
			redir = ft_ast_new_redir(op, redir_arg, root);
			if (!redir)
				return (free_segs(redir_arg), free_ast(&root), NULL);
			root = redir;
		}
	}
	return (root);
}
