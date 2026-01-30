/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:44 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:59:15 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	ft_exec_ast(t_ast *node, t_shell *shell)
{
	int	status;

	if (node == NULL)
		return (0);
	if (node->type == NODE_PIPE)
		status = ft_exec_pipe(node, shell);
	else if (node->type == NODE_CMD)
		status = ft_exec_cmd(node, shell);
	else if (node->type == NODE_SUBSHELL)
		status = ft_exec_subshell(node, shell);
	else if (node->type == NODE_AND)
		status = ft_exec_and(node, shell);
	else if (node->type == NODE_OR)
		status = ft_exec_or(node, shell);
	else if (node->type == NODE_HEREDOC)
		return (ft_exec_here_doc(node, shell));
	else if (node->type == NODE_REDIR_IN)
		status = ft_exec_redirect_in(node, shell);
	else if (node->type == NODE_REDIR_OUT)
		status = ft_exec_redirect_out(node, shell);
	else if (node->type == NODE_REDIR_APPEND)
		status = ft_exec_append(node, shell);
	else
		status = 0;
	return (status);
}
