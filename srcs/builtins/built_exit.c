#include "../../includes/builtins.h"

static t_bool	ft_is_valid_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (FALSE);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FALSE);
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
		digit = *s - '0';
		if (digit < 0 || digit > 9)
			return (FALSE);
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

static t_bool	ft_check_overflow(char *s)
{
	int	sign;

	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	return (*s && ft_verif(s, sign));
}

int	ft_exit(char **args, t_shell *shell)
{
	long	status;

	if (shell->interactive)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args[1])
		return (shell->should_exit = 1, shell->last_status);
	if (args[2])
	{
		ft_putstr_fd("minishield: exit: too many arguments\n", STDERR_FILENO);
		shell->last_status = 1;
		return (1);
	}
	if (!ft_is_valid_numeric(args[1]) || !ft_check_overflow(args[1]))
	{
		ft_putstr_fd("minishield: exit: numeric argument required\n",
			STDERR_FILENO);
		shell->last_status = 2;
		shell->should_exit = 1;
		return (2);
	}
	status = ft_atol(args[1]);
	return (shell->last_status = (unsigned char)status,
		shell->should_exit = 1, shell->last_status);
}

