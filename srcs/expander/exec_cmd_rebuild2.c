/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_rebuild2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:17:40 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:17:41 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/expander.h"

static int	ft_arg_restorer(char **arg)
{
	int		j;
	char	*s;
	char	*new;

	s = *arg;
	j = 0;
	while (s && s[j])
	{
		if (s[j] == '\x1F')
			s[j] = ' ';
		j++;
	}
	if (s && s[0] == '\x1E' && s[1] == '\0')
	{
		new = ft_strdup("");
		if (!new)
			return (0);
		free(*arg);
		*arg = new;
	}
	return (1);
}

int	ft_restore_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (!ft_arg_restorer(&args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_empty(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
			return (0);
	}
	return (1);
}

int	ft_set_empty_cmd(t_ast *n, char *ret)
{
	free(ret);
	ft_free_args(n->args);
	n->args = NULL;
	return (1);
}

int	ft_cmd_rebuild2(t_ast *n, char **ret)
{
	char	**nargs;

	nargs = ft_split(*ret, ' ');
	free(*ret);
	if (!nargs)
		return (0);
	if (!nargs[0])
		return (ft_free_args(nargs), ft_free_args(n->args), n->args = NULL, 1);
	if (!ft_restore_args(nargs))
		return (ft_free_args(nargs), 0);
	ft_free_args(n->args);
	n->args = nargs;
	if (!ft_args_handler(n))
		return (ft_free_args(n->args), n->args = NULL, 0);
	return (1);
}
