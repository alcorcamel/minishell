
#include "../../includes/builtins.h"

static int	ft_verif_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (1);
	while (args[i])
		i++;
	if (i == 1)
		return (2);
	return (0);
}

static int	ft_skip_space(int i, char **args)
{
	int	j;

	j = 0;
	while (args[i][j] && args[i][j] == 32)
		j++;
	return (j);
}

static void	ft_assign_as_n(t_bool *as_n, char **args, int *i, int *j)
{
	while (args[++(*i)])
	{
		*j = ft_skip_space(*i, args);
		if (!args[*i][*j] || args[*i][*j] != '-')
		{
			if (*i == 1)
				*as_n = FALSE;
			break ;
		}
		(*j)++;
		if (!args[*i][*j] || args[*i][*j] != 'n')
		{
			if (*i == 1)
				*as_n = FALSE;
			break ;
		}
		while (args[*i][*j] && args[*i][*j] == 'n')
			(*j)++;
		if (args[*i][*j] != '\0')
		{
			if (*i == 1)
				*as_n = FALSE;
			break ;
		}
	}
}

int	ft_echo(char **args)
{
	int		i;
	int		j;
	t_bool	as_n;

	if (ft_verif_args(args) == 1)
		return (0);
	if (ft_verif_args(args) == 2)
		return (ft_printf("\n"), 0);
	i = 0;
	as_n = TRUE;
	ft_assign_as_n(&as_n, args, &i, &j);
	if (!args[i])
	{
		if (as_n == TRUE)
			return (0);
		else
			ft_printf("\n");
	}
	while (args[i + 1] != NULL)
		ft_printf("%s ", args[i++]);
	if (as_n == TRUE)
		ft_printf("%s", args[i]);
	else
		ft_printf("%s\n", args[i]);
	return (0);
}
