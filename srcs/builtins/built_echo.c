
#include "../../includes/builtins.h"

int	ft_echo(char **arg)
{
	int		i;
	int		j;
	t_bool	as_n;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
		i++;
	if (i == 1)
		return (ft_printf("\n"), 0);
	i = 1;
	as_n = TRUE;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j] && arg[i][j] == 32)
			j++;
		if (!arg[i][j] || arg[i][j] != '-')
		{
			if (i == 1)
				as_n = FALSE;
			break ;
		}
		j++;
		if (!arg[i][j] || arg[i][j] != 'n')
		{
			if (i == 1)
				as_n = FALSE;
			break ;
		}
		while (arg[i][j] && arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
		{
			if (i == 1)
				as_n = FALSE;
			break ;
		}
		i++;
	}
	if (!arg[i])
	{
		if (as_n == TRUE)
			return (0);
		else
			ft_printf("\n");
	}
	while (arg[i + 1] != NULL)
		ft_printf("%s ", arg[i++]);
	if (as_n == TRUE)
		ft_printf("%s", arg[i]);
	else
		ft_printf("%s\n", arg[i]);
	return (0);
}
// int	main(void)
// {
// 	char *test[] = {
// 		"echo",
// 		"-nnnn",
// 		"-nnnn",
// 		"-nnnn",
// 		"akim",
// 		"emane",
// 		NULL
// 	};

// 	ft_printf("result = %d\n", echo(test));
// 	return (0);
// }
