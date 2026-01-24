#include "../../includes/expander.h"

int	ft_valid_any3(char *arg, char *line, int *i, int *j)
{
	while (arg[*j] && arg[*j] == line[*i])
	{
		(*i)++;
		(*j)++;
	}
	if (arg[*j] == '\0' && line[*i] == '\0')
		return (1);
	if (arg[*j] != '\x1D' && arg[*j] != line[*i])
		return (0);
	return (2);
}

int	ft_valid_any2(char *arg, char *line, int *i, int *j)
{
	while (arg[(*j)] == '\x1D')
		(*j)++;
	if (!arg[*j])
		return (1);
	while (line[*i] && line[*i] != arg[*j])
		(*i)++;
	if (!line[*i])
		return (0);
	if (ft_valid_star_any(line + *i + 1, arg + (*j) - 1))
		return (1);
	if (arg[*j] && line[*i] != arg[*j])
		return (0);
	if (!arg[*j] && !line[*i])
		return (1);
	return (2);
}

int	ft_star_any_init(char *arg, char *line)
{
	if (arg[0] == '\x1D' && line[0] == '.')
		return (0);
	if (!line[0])
		return (0);
	return (1);
}

int	ft_valid_star_any(char *line, char *arg)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	if (!ft_star_any_init(arg, line))
		return (0);
	while (1)
	{
		if (arg[j] == '\x1D')
			ret = ft_valid_any2(arg, line, &i, &j);
		else
			ret = ft_valid_any3(arg, line, &i, &j);
		if (ret == 0)
			return (0);
		if (ret == 1)
			return (1);
	}
}
