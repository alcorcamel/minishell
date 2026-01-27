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
