#include "../../includes/executor.h"
#include "../../includes/expander.h"

int	ft_is_empty_noifs(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = -1;
	while (s[++i])
	{
		if (s[i] != '\x1A')
			return (0);
	}
	return (1);
}

int	ft_cmd_rebuild2_noifs(t_ast *n, char **ret)
{
	char	**nargs;

	nargs = ft_split(*ret, '\x1A');
	free(*ret);
	if (!nargs)
		return (0);
	if (!nargs[0])
		return (ft_free_args(nargs), ft_free_args(n->args), n->args = NULL, 1);
	if (!ft_restore_args(nargs))
		return (ft_free_args(nargs), 0);
	ft_free_args(n->args);
	n->args = nargs;
	if (!ft_args_handler(n))
		return (ft_free_args(n->args), n->args = NULL, 0);
	return (1);
}
