#include "../../includes/executor.h"

int	ft_exec_built(t_ast *node, t_shell *shell)
{
	if (!node || !node->args || !node->args[0])
		return (FALSE);
	if (ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])) == 0)
		return (ft_echo(node->args));
	if (ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0]))  == 0)
		return (ft_cd(node->args));
	if (ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0]))  == 0)
		return (ft_pwd(node->args));
	if (ft_strncmp(node->args[0], "export", ft_strlen(node->args[0]))  == 0)
		return (ft_export(node->args, shell));
	if (ft_strncmp(node->args[0], "unset", ft_strlen(node->args[0])) == 0)
		return (ft_unset(node->args, shell));
	if (ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])) == 0)
		return (ft_env(node->args, shell));
	if (ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])) == 0)
		return (ft_exit(node->args));
	return (FALSE);
}
