/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_throw_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:14 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:19:15 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/executor.h"

int	ft_print_err_directory(char *dir)
{
	ft_putstr_fd("minishield: ", STDERR_FILENO);
	if (dir)
		ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
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
		ft_putstr_fd("minishield: ", STDERR_FILENO);
		if (err_p)
			ft_putstr_fd(err_p, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishield: ", STDERR_FILENO);
		if (err_p)
			ft_putstr_fd(err_p, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (127);
}
