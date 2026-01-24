#include "../../includes/expander.h"

void	ft_sort2(t_new_args **h, t_new_args **e, t_new_args **tmp, char **bkp)
{
	while ((*h)->next && (*h)->next->globbed == 1)
	{
		*tmp = (*h)->next;
		while (*tmp && *tmp != (*e)->next)
		{
			if ((*tmp)->globbed == 1
				&& ft_str_compare((*h)->value, (*tmp)->value) > 0)
			{
				*bkp = (*tmp)->value;
				(*tmp)->value = (*h)->value;
				(*h)->value = *bkp;
			}
			*tmp = (*tmp)->next;
		}
		(*h) = (*h)->next;
	}
	*tmp = (*e)->next;
}

void	ft_sublist_sorter(t_new_args **head, t_ast *n)
{
	t_new_args	*tmp;
	t_new_args	*new_head;
	t_new_args	*end;
	char		*bkp;

	(void)n;
	if (!head || !(*head))
		return ;
	tmp = *head;
	while (tmp)
	{
		while (tmp && tmp->globbed == 0)
			tmp = tmp->next;
		new_head = tmp;
		if (!new_head)
			return ;
		end = new_head;
		while (end->next && end->next->globbed == 1)
			end = end->next;
		ft_sort2(&new_head, &end, &tmp, &bkp);
	}
}

int		ft_args_handler_loop(t_ast *n, int *found, int *i, t_new_args **head)
{
	t_new_args	*tmp;
	char		*s;

	if (ft_strchr(n->args[*i], (int)'\x1D'))
	{
		*found = 1;
		if (!ft_star_anywhere(head, n->args[*i]))
			return (0);
	}
	else
	{
		s = ft_strdup(n->args[*i]);
		if (!s)
			return (0);
		tmp = ft_argnew(s);
		if (!tmp)
			return (free(s), 0);
		ft_arg_add_back(head, tmp, 0);
	}
	return (1);
}

int		ft_args_handler(t_ast *n)
{
	int			i;
	char		**ret;
	t_new_args	*head;
	int			found;

	i = -1;
	found = 0;
	ret = NULL;
	head = NULL;
	if (!n || !n->args)
		return (0);
	while (n->args[++i])
	{
		if (!ft_args_handler_loop(n, &found, &i, &head))
			return (ft_free_nargs(head), 0);//appel de la fonction qui free tout)
	}
	if (found)
		ft_sublist_sorter(&head, n);
	if (!ft_new_args_maker(&head, n))
		return (ft_free_nargs(head), 0);//appel de la fonction qui free tout
	ft_free_nargs(head);
	return (1);
}
