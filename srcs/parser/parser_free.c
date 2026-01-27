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
		ft_free((void **)&tmp->value);
		ft_free((void **)&tmp);
		tmp = next;
	}
	*tok = NULL;
}

void	ft_free_token(t_token **tok)
{
	t_token	*next;
	t_token	*tmp;

	tmp = *tok;
	while (tmp)
	{
		next = tmp->next;
		ft_free((void **)&tmp->value);
		ft_free_segs(&tmp->segs);
		ft_free((void **)&tmp);
		tmp = next;
	}
	*tok = NULL;
}

void	ft_ast_cleaner(t_ast *n)
{
	ft_free((void **)&n->filename);
	ft_free((void **)&n->limiter);
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
	ft_free((void **)&(*root));
	*root = NULL;
}
