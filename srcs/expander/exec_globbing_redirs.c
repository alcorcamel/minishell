/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_globbing_redirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:17:50 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:17:50 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

int	ft_valid_inout3(char *arg, char *line, int *i, int *j)
{
	while (arg[*j] && arg[*j] == line[*i])
	{
		(*i)++;
		(*j)++;
	}
	if (arg[*j] == '\0' && line[*i] == '\0')
		return (1);
	if (arg[*j] != '*' && arg[*j] != line[*i])
		return (0);
	return (2);
}

int	ft_valid_inout2(char *arg, char *line, int *i, int *j)
{
	while (arg[(*j)] == '*')
		(*j)++;
	if (!arg[*j])
		return (1);
	while (line[*i] && line[*i] != arg[*j])
		(*i)++;
	if (!line[*i])
		return (0);
	if (ft_valid_star_any_inout(line + *i + 1, arg + (*j) - 1))
		return (1);
	if (arg[*j] && line[*i] != arg[*j])
		return (0);
	if (!arg[*j] && !line[*i])
		return (1);
	return (2);
}

int	ft_star_inout_init(char *arg, char *line)
{
	if (arg[0] == '*' && line[0] == '.')
		return (0);
	if (!line[0])
		return (0);
	return (1);
}

int	ft_valid_star_any_inout(char *line, char *arg)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	if (!ft_star_inout_init(arg, line))
		return (0);
	while (1)
	{
		if (arg[j] == '*')
			ret = ft_valid_inout2(arg, line, &i, &j);
		else
			ret = ft_valid_inout3(arg, line, &i, &j);
		if (ret == 0)
			return (0);
		if (ret == 1)
			return (1);
	}
}
