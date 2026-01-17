#include "../../includes/builtins.h"


int	ft_export(char **args, t_shell *shell)
{
	if (!args[1])
		return (ft_print_envp(shell));
	return (0);
}

