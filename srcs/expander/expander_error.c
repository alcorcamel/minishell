/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:09 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 10:27:22 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	ft_expander_error(char *s, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishield: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ambigous redirect\n", 2);
	}
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
