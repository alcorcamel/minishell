#include "../../includes/expander.h"

t_new_args	*ft_argnew(char *value)
{
	t_new_args	*ret;

	ret = (t_new_args *)ft_calloc(1, sizeof(t_new_args));
	if (!ret)
		return (NULL);
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

int	ft_arg_restorer_bis(char *arg)
{
	int	i;
	int	size;

	i = -1;
	if (!arg)
		return (0);
	size = ft_strlen(arg);
	while (++i < size)
	{
		if (arg[i] == '\x1D')
			arg[i] = '*';
	}
	return (1);
}

int	ft_spechar_counter(char *arg)
{
	int	i;
	int	size;
	int	ret;

	i = -1;
	ret = 0;
	if (!arg)
		return (0);
	size = ft_strlen(arg);
	while (++i < size)
	{
		if (arg[i] == '\x1D')
			ret++;
	}
	return (ret);
}

int	ft_arg_lstsize(t_new_args *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_spe_arg_lstsize(t_new_args *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->globbed == 1)
			i++;
		lst = lst->next;
	}
	return (i);
}
