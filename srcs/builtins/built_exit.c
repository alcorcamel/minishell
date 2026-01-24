#include "../../includes/builtins.h"

int	ft_print_err_exit(void)
{
	ft_putstr_fd("minishield: exit : too many arguments\n", STDERR_FILENO);
	return (1);
}

void	ft_print_err_exit_nb_args(void)
{
	ft_putstr_fd("minishield: exit : numeric argument required\n",
		STDERR_FILENO);
	exit(2);
}

static t_bool	ft_is_valid_args_exit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-' || arg[i] != '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			// free tout avant !!!
			ft_print_err_exit_nb_args();
			return (FALSE);
			break ;
		}
		i++;
	}
	return (TRUE);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	status;
	int	i;

	ft_printf("exit\n");
	if (!args[1])
		exit(shell->last_status);
	// a verifier le code d exit poiur un overflow
	if (args[2] && ft_is_valid_args_exit(args[1]))
		return (ft_print_err_exit());
	i = 0;
	if (ft_is_valid_args_exit(args[1]) == FALSE)
		ft_print_err_exit_nb_args();
	// verifier l overflow!!!
	status = ft_atoi(args[1]);
	status = status % 256;
	// free_tout avant ilf aut pas oublier!!!!!
	exit(status);
	return (0);
}
