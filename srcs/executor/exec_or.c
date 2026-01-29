/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:02 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:22:25 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	ft_exec_or(t_ast *node, t_shell *shell)
{
	int	status;

	status = ft_exec_ast(node->left, shell);
	if (status != 0)
		return (ft_exec_ast(node->right, shell));
	return (status);
}
