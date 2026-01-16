
#include "../../includes/executor.h"

int	ft_exec_and(t_ast *node, t_shell *shell)
{
	int	status;

	status = ft_exec_root(node->left, shell);
	if (status == 0)
		return (ft_exec_ast(node->right, shell));
	exit(status);
}
