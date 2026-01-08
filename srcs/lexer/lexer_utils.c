/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:40:55 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/07 21:55:04 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_remi.h"

int	ft_isspaces(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_is_brace(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
	}

int	ft_is_an_operator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

int	ft_is_sep(char c)
{
	if (c == '\0' || ft_isspaces(c) || ft_is_brace(c) || ft_is_an_operator(c))
		return (1);
	return (0);
}

char	*ft_strndup(const char *s, int n)
{
	char	*ret;
	int		i;

	ret = (char *)malloc((size_t)n + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
