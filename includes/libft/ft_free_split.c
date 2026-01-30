/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:03:31 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:58:49 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***split)
{
	char	**free_val;
	int		i;

	if (!split)
		return ((void)0);
	free_val = *split;
	if (!free_val)
		return ((void)0);
	i = 0;
	while (free_val[i])
	{
		ft_free((void **)&free_val[i]);
		i++;
	}
	ft_free((void **)&free_val);
	*split = NULL;
}
