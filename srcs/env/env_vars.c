#include "../../includes/env.h"

t_vars	*ft_find_vars(char *key, t_shell *shell)
{
	t_vars	*iterator;

	iterator = shell->vars;
	while (iterator != NULL)
	{
		if (ft_strncmp(key, iterator->key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(iterator->key))
			return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}

static void	ft_free_vars(t_vars **var)
{
	ft_free((void **)&(*var)->key);
	ft_free((void **)&(*var)->value);
	ft_free((void **)&(*var));
}

t_bool	ft_del_vars(t_vars *del, t_shell *shell)
{
	t_vars	*iterator;
	t_vars	*prev;

	iterator = shell->vars;
	prev = NULL;
	if (del == NULL || shell->vars == NULL)
		return (TRUE);
	while (iterator)
	{
		if (ft_strncmp(iterator->key, del->key, ft_strlen(del->key)) == 0
			&& ft_strlen(del->key) == ft_strlen(iterator->key))
		{
			if (prev)
				prev->next = iterator->next;
			else
				shell->vars = iterator->next;
			ft_free_vars(&iterator);
			return (TRUE);
		}
		prev = iterator;
		iterator = iterator->next;
	}
	return (FALSE);
}
