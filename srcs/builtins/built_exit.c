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
			return ((FALSE));
			break ;
		}
		i++;
	}
	return (TRUE);
}

static t_bool	ft_verif(char *s, int sign)
{
	unsigned long	result;
	int				digit;

	result = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (FALSE);

		digit = *s - '0';
		if (sign == 1)
		{
			if (result > (unsigned long)(LONG_MAX - digit) / 10)
				return (FALSE);
		}
		else
		{
			if (result > (unsigned long)(-(LONG_MIN + digit)) / 10)
				return (FALSE);
		}
		result = result * 10 + digit;
		s++;
	}
	return (TRUE);
}

static t_bool	ft_verif_overflow(char *s)
{
	int				sign;

	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (FALSE);
	return (ft_verif(s, sign));
}

int	ft_exit(char **args, t_shell *shell)
{
	int	status;
	int	i;

	ft_printf("exit\n");
	if (!args[1])
	{
		ft_free_shell(&shell);
		exit(shell->last_status);
	}
	if (args[2] && ft_is_valid_args_exit(args[1], shell))
		return (ft_print_err_exit());
	i = 0;
	if (ft_is_valid_args_exit(args[1], shell) == (FALSE))
		ft_print_err_exit_nb_args(shell);
	if (ft_verif_overflow(args[1]) == (FALSE))
		return (ft_print_err_exit_nb_args(shell), 2);
	status = ft_atol(args[1]);
	status = status % 256;
	ft_free_shell(&shell);
	exit(status);
	return (0);
}
