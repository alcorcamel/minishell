#include "../../includes/builtins.h"

int	ft_print_err_exit(void)
{
	ft_putstr_fd("minishield: exit : trop d'arguments\n", STDERR_FILENO);
	return (1);
}

void	ft_print_err_exit_nb_args(void)
{
	ft_putstr_fd("minishield: exit : argument numérique nécessaire\n",
		STDERR_FILENO);
	exit(2);
}

int		ft_exit(char **arg)
{
	int	status;
	int	i;

	ft_printf("exit\n");
	if (!arg[1])
		exit(0);
	// a verifier le code d exit poiur un overflow
	if (arg[2])
		return (ft_print_err_exit());
	i = 0;
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]) && arg[1][i] != '-' && arg[1][i] != '+')
		{
			// free tout avant !!!
			ft_print_err_exit_nb_args();
			break ;
		}
		i++;
	}
	// verifier l overflow!!!
	status = ft_atoi(arg[1]);
	status = status % 256;
	// free_tout avant ilf aut pas oublier!!!!!
		exit(status);
	return (0);
}
