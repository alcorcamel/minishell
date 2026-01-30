/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_throw_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:14 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 10:27:02 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	ft_print_err_directory(char *dir)
{
	if (dir)
	{
		ft_putstr_fd("minishield: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
		ft_putstr_fd("minishield: : Is a directory\n", 2);
	return (126);
}

int	ft_throw_error_cmd(char *cmd)
{
	if (cmd && ft_is_directory(cmd) == TRUE && ft_strchr(cmd, '/'))
		return (ft_print_err_directory(cmd));
	ft_perror(cmd);
	if (errno == EACCES || errno == ENOEXEC)
		return (126);
	if (errno == ENOENT)
		return (127);
	return (1);
}

int	ft_throw_error(char *cmd)
{
	ft_perror(cmd);
	if (errno == EACCES || errno == ENOEXEC)
		return (126);
	if (errno == ENOENT)
		return (127);
	return (1);
}

int	ft_throw_error_cmd_not_found(char *err_p)
{
	if (ft_strchr(err_p, '/'))
	{
		if (err_p)
		{
			ft_putstr_fd("minishield: ", 2);
			ft_putstr_fd(err_p, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			ft_putstr_fd("minishield: : No such file or directory\n", 2);
	}
	else
	{
		if (err_p)
		{
			ft_putstr_fd("minishield: ", 2);
			ft_putstr_fd(err_p, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
			ft_putstr_fd("minishield: : command not found\n", 2);
	}
	return (127);
}
