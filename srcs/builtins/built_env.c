#include "../../includes/builtins.h"

static int	ft_print_err_env(void)
{
	ft_putstr_fd("minishield: env: too many arguments\n", STDERR_FILENO);
	return (1);
}

int	ft_env(char **args, t_shell *shell)
{
	if (args[1])
		return (ft_print_err_env());
	return (ft_print_envp(shell, FALSE));
}
