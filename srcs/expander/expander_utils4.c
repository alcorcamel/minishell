/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:27 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:18:27 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	ft_str_capitalizer(char *str)
{
	size_t	size;
	size_t	i;

	if (!str)
		return ;
	size = ft_strlen(str);
	i = -1;
	while (++i < size)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

int	ft_str_compare(char *s1, char *s2)
{
	char	*tmp1;
	char	*tmp2;
	int		ret;

	if (!s1 || !s2)
		return (0);
	tmp1 = ft_strdup(s1);
	tmp2 = ft_strdup(s2);
	if (!tmp1 || !tmp2)
		return (free(tmp1), free(tmp2), 0);
	ft_str_capitalizer(tmp1);
	ft_str_capitalizer(tmp2);
	ret = strcmp(tmp1, tmp2);
	return (free(tmp1), free(tmp2), ret);
}

void	ft_arg_add_back(t_new_args **lst, t_new_args *new, int i)
{
	t_new_args	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		if (i == 1)
			new->globbed = 1;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	if (i == 1)
		new->globbed = 1;
}
