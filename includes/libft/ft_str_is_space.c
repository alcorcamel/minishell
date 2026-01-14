/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 01:03:58 by demane            #+#    #+#             */
/*   Updated: 2025/12/25 01:27:36 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_space(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] != 32)
			res = 0;
	}
	return (res);
}
