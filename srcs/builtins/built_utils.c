#include "../../includes/builtins.h"

t_bool	ft_is_builtin(t_ast *node, t_shell *shell)
{
	if (!node || !node->args || !node->args[0])
		return (FALSE);
	if (ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	if (ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	if (ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	if (ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	if (ft_strncmp(node->args[0], "unset", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	if (ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	if (ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])) == 0)
		return (TRUE);
	return (FALSE);
}

