/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:09 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:18:09 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	ft_expander_error(char *s, int i)
{
	if (i == 1)
		printf("bash: %s: ambigous redirect\n", s);
}

void	ft_free_nargs(t_new_args *node)
{
	t_new_args	*next;

	while (node)
	{
		next = node->next;
		free(node->value);
		free(node);
		node = next;
	}
}
