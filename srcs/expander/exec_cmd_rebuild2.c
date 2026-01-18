#include "../../includes/executor.h"
#include "../../includes/expander.h"

static int	ft_arg_restorer(char **arg)
{
	int		j;
	char	*s;
	char	*new;

	s = *arg;
	j = 0;
	while (s && s[j])
	{
		if (s[j] == '\x1F')
			s[j] = ' ';
		j++;
	}
	if (s && s[0] == '\x1E' && s[1] == '\0')
	{
		new = ft_strdup("");
		if (!new)
			return (0);
		free(*arg);
		*arg = new;
	}
	return (1);
}

int	ft_restore_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (!ft_arg_restorer(&args[i]))
			return (0);
		i++;
	}
	return (1);
}
