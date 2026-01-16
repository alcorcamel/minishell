#include "../../includes/builtins.h"


int	ft_export(char **args, t_shell *shell)
{
	if (!args[1])
		ft_print_envp(shell->envp);
}

