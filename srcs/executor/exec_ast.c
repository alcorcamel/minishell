#include "executor.h"

// a mettre avant d executer cette fonction
// signal(SIGNINT, SIG_IGN)
// permet d ignorer le signal dans le process parent
// on le restaura dans les differentes commandes

int	ft_exec_ast(t_ast *node, t_shell *shell)
{
	int	status;

	if (node == NULL)
		exit(0);
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
	// if (node->type == NODE_HEREDOC)
	// 	return (ft_exec_heredoc(node, shell));
	else if (node->type == NODE_REDIR_IN || node->type == NODE_HEREDOC)
		status = ft_exec_redirect_in(node, shell);
	else if (node->type == NODE_REDIR_OUT)
		status = ft_exec_redirect_out(node, shell);
	else
		status = 0;
	// if (node->type == NODE_REDIR_APPEND)
	// 	return (ft_exec_redirect_append(node, shell));
	exit(status);
}
