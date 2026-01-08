#include "executor.h"

void	ft_exec_cmd(t_ast *node)
{
	if (ft_is_builtin(node))
		ft_exec_builtin(node);

}
