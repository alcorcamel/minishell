/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:16:50 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:16:51 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';' || c == '\\')
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
