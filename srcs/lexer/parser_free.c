
#include "lexer.h"

void	free_ast(t_ast **root)
{
	t_ast	*n;

	if (!root || !*root)
		return ;

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
