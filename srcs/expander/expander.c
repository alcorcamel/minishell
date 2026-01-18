
#include "../../includes/expander.h"

static int	ft_rebuild_node(t_ast *n, t_shell *shell)
{
	if (n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
		|| n->type == NODE_REDIR_APPEND)
	{
		if (!ft_redir_rebuild(n))
			return (0);// gestion erreur
	}
	// if (n->type == NODE_CMD)
	// {
	// 	if (!ft_cmd_expand(n, shell))
	// 		return (0);// gestion erreur
	// }
	return (1);
}

static int	ft_expand_node(t_ast *n, t_shell *shell)
{
	// if (n->type == NODE_CMD)
	// {
	// 	if (!ft_cmd_rebuild(n))
	// 		return (0);// gestion erreur
	// }
	if (n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
		|| n->type == NODE_REDIR_APPEND)
	{
		if (!ft_redir_expand(n, shell))
			return (0);// gestion erreur
	}
	if (n->type == NODE_HEREDOC)
	{
		if (!ft_heredoc_rebuild(n))
			return (0);// gestion erreur
	}
	return (1);
}

void	ft_explore_ast(t_ast **root, t_shell *shell)
{
	t_ast	*n;

	if (!root || !*root)
		return ;
	n = *root;
	if (!ft_expand_node(n, shell))
		return ;
	if (!ft_rebuild_node(n, shell))
		return ;
	if (n->left)
		ft_explore_ast(&n->left, shell);
	if (n->right)
		ft_explore_ast(&n->right, shell);
}
