/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:47 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 00:02:33 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	ft_exec_built(t_ast *node, t_shell *shell)
{
	if (!node || !node->args || !node->args[0])
		return (FALSE);
	if (!ft_strncmp(node->args[0], "echo", 4) && ft_strlen(node->args[0]) == 4)
		return (ft_echo(node->args));
	if (!ft_strncmp(node->args[0], "cd", 2) && ft_strlen(node->args[0]) == 2)
		return (ft_cd(node->args, shell));
	if (!ft_strncmp(node->args[0], "pwd", 3) && ft_strlen(node->args[0]) == 3)
		return (ft_pwd(node->args));
	if (!ft_strncmp(node->args[0], "export", 6) \
&& ft_strlen(node->args[0]) == 6)
		return (ft_export(node->args, shell));
	if (!ft_strncmp(node->args[0], "unset", 5) && ft_strlen(node->args[0]) == 5)
		return (ft_unset(node->args, shell));
	if (!ft_strncmp(node->args[0], "env", 3) && ft_strlen(node->args[0]) == 3)
		return (ft_env(node->args, shell));
	if (!ft_strncmp(node->args[0], "exit", 4) && ft_strlen(node->args[0]) == 4)
		return (ft_exit(node->args, shell));
	return (FALSE);
}
