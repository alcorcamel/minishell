/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_throw_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:14 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:43:18 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	ft_print_err_directory(char *dir)
{
	if (dir)
		ft_printf_fd(STDERR_FILENO, "minishield: %s: \
Is a directory\n", dir);
	else
		ft_printf_fd(STDERR_FILENO, "minishield: : \
Is a directory\n");
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
			ft_printf_fd(STDERR_FILENO, "minishield: %s: \
No such file or directory\n", err_p);
		else
			ft_printf_fd(STDERR_FILENO, "minishield: : \
No such file or directory\n");
	}
	else
	{
		if (err_p)
			ft_printf_fd(STDERR_FILENO, "minishield: %s: \
command not found\n", err_p);
		else
			ft_printf_fd(STDERR_FILENO, "minishield: : \
command not found\n");
	}
	return (127);
}
