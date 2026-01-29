# include "../../includes/env.h"

void	ft_free_all_env(t_vars **head)
{
	t_vars	*next;

	while (*head)
	{
		next = (*head)->next;
		ft_free((void **)&((*head)->value));
		ft_free((void **)&((*head)->key));
		ft_free((void **)&(*head));
		*head = next;
	}
}

void	ft_free_all_envp(char ***envp)
{
	int		i;
	char	**freee;

	if (!envp || !*envp)
		return ((void)0);
	i = -1;
	freee = *envp;
	while (freee[++i])
	{
		ft_free((void **)&freee[i]);
	}
	ft_free((void **)&(*envp));
}
