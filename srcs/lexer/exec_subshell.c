
#include "lexer.h"
// pas gerer le cas pid == -1

int		ft_exec_subshell(t_ast *node, t_shell *shell)
{
	return (ft_exec_root(node->left, shell));
}
