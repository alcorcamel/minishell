#include "../../includes/parser.h"
#include "../../includes/expander.h"

void	ft_free_new_args(t_new_args **tok)
{
	t_new_args	*next;
	t_new_args	*tmp;

	tmp = *tok;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
}

void	ft_free_token(t_token **tok)
{
	t_token	*next;
	t_token	*tmp;

	tmp = *tok;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		ft_free_segs(&tmp->segs);
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
}

void	ft_ast_cleaner(t_ast *n)
{
	if (n->type == NODE_HEREDOC && n->filename)
		unlink(n->filename);
	free(n->filename);
	n->filename = NULL;
	free(n->limiter);
	n->limiter = NULL;
	ft_free_segs(&n->segs);
	ft_free_args(n->args);
}

void	ft_free_ast(t_ast **root)
{
	t_ast	*n;

	if (!root || !*root)
		return ;
	n = *root;
	if (n->left)
		ft_free_ast(&n->left);
	if (n->right)
		ft_free_ast(&n->right);
	ft_ast_cleaner(n);
	free(*root);
	*root = NULL;
}
