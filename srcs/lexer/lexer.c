/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:53:41 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/08 13:10:12 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*ft_lexer(char *l)
{
	int		i;
	t_token	*lst_begin;

	i = 0;
	if (!l)
		return (NULL);
	lst_begin = NULL;
	while (l[i])
	{
		while (ft_isspaces(l[i]))
			i++;
		if (!l[i])
			break ;
		if (ft_is_brace(l[i]) || ft_is_an_operator(l[i]))
		{
			if (!ft_add_operator(&lst_begin, l, &i))
				return (ft_free_tokens(lst_begin), NULL);
		}
		else
		{
			if (!ft_read_word(&lst_begin, l, &i))
				return (ft_free_tokens(lst_begin), NULL);
		}
	}
	return (lst_begin);
}
