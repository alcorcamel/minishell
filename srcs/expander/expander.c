#include "../../includes/expander.h"

static int	ft_expand_node(t_ast *n, t_shell *shell)
{
	if (n->type == NODE_HEREDOC)
	{
		if (!ft_heredoc_rebuild(n, shell))
			return (0);
	}
	return (1);
}

int	ft_explore_ast(t_ast **root, t_shell *shell)
{
	t_ast	*n;

	if (!root || !*root)
		return (0);
	n = *root;
	if (!ft_expand_node(n, shell))
		return (0);
	if (n->left && !ft_explore_ast(&n->left, shell))
		return (0);
	if (n->right && !ft_explore_ast(&n->right, shell))
		return (0);
	return (1);
}
