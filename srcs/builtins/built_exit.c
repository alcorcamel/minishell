#include "../../includes/builtins.h"

int	ft_print_err_exit(void)
{
	ft_putstr_fd("minishield: exit : too many arguments\n", STDERR_FILENO);
	return (1);
}

static void	ft_print_err_exit_nb_args(t_shell *shell)
{
	ft_putstr_fd("minishield: exit : numeric argument required\n",
		STDERR_FILENO);
	ft_free_shell(&shell);
	exit(2);
}

static t_bool	ft_is_valid_args_exit(char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	if (arg[i] != '-' || arg[i] != '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_print_err_exit_nb_args(shell);
			return (FALSE);
			break ;
		}
		i++;
	}
	return (TRUE);
}

static t_bool	ft_verif_overflow(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (FALSE);
		if (result > (LONG_MAX - (*s - '0')) / 10)
			return (FALSE);
		result = result * 10 + (*s - '0');
		s++;
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
	if (args[2] && ft_is_valid_args_exit(args[1], shell))
		return (ft_print_err_exit());
	i = 0;
	if (ft_is_valid_args_exit(args[1], shell) == FALSE)
		ft_print_err_exit_nb_args(shell);
	if (ft_verif_overflow(args[1]) == FALSE)
		return (ft_print_err_exit_nb_args(shell), 2);
	status = ft_atol(args[1]);
	status = status % 256;
	ft_free_shell(&shell);
	exit(status);
	return (0);
}
