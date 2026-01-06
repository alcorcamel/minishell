/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:53:41 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/06 22:35:57 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_remi.h"

static int	ft_double_size_operator(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 1;
	if (s[i + 1] && s[i + 1] == s[i])
		return (1);
	return (0);
}

t_token		*ft_lexer(char *l)
{
	int	i;

	i = -1;
	if (!l)
		return (NULL);
	while (l[++i])
	{


		if (l[i] == '<' || l[i] == '>' || l[i] == '|' || l[i] == '&')
		{
			if (ft_double_size_operator(l + i) == 1)
				// ajout noeud token double operator
			else
				// ajout noeud oprator simple
		}



	}
}
