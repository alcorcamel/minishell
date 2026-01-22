#include "../../includes/builtins.h"

int	ft_unset(char **args, t_shell *shell)
{
	t_vars	*search;
	int		i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i] != NULL)
	{
		search = ft_find_vars(args[i], shell);
		if (search != NULL)
			ft_del_vars(search, shell);
		i++;
	}
	return (0);
}
