#include "../../includes/builtins.h"

t_bool	ft_is_builtin(t_ast *node, t_shell *shell)
{
	(void)shell;
	if (!node || !node->args || !node->args[0])
		return (FALSE);
	if (!ft_strncmp(node->args[0], "echo", 4) && ft_strlen(node->args[0]) == 4)
		return (TRUE);
	if (!ft_strncmp(node->args[0], "cd", 2) && ft_strlen(node->args[0]) == 2)
		return (TRUE);
	if (!ft_strncmp(node->args[0], "pwd", 3) && ft_strlen(node->args[0]) == 3)
		return (TRUE);
	if (!ft_strncmp(node->args[0], "export", 6) \
		&& ft_strlen(node->args[0]) == 6)
		return (TRUE);
	if (!ft_strncmp(node->args[0], "unset", 5) && ft_strlen(node->args[0]) == 5)
		return (TRUE);
	if (!ft_strncmp(node->args[0], "env", 3) && ft_strlen(node->args[0]) == 3)
		return (TRUE);
	if (!ft_strncmp(node->args[0], "exit", 4) && ft_strlen(node->args[0]) == 4)
		return (TRUE);
	return (FALSE);
}

