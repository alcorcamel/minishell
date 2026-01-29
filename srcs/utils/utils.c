/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:20:09 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:20:10 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_bool	ft_is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (FALSE);
	if (S_ISDIR(st.st_mode) == 0)
		return (FALSE);
	return (TRUE);
}

void	ft_perror(char *err_p)
{
	char	*join;

	join = ft_strjoin("minishield: ", err_p);
	if (!join)
		return ((void)0);
	perror(join);
	ft_free((void **)&join);
}

void	ft_free_shell(t_shell **shell)
{
	if ((*shell)->vars)
		ft_free_all_env(&((*shell)->vars));
	if ((*shell)->root_ast)
		ft_free_ast(&((*shell)->root_ast));
}
