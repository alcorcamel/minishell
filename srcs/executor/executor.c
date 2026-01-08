#include "executor.h"

// a mettre avant d executer cette fonction
// signal(SIGNINT, SIG_IGN)
// permet d ignorer le signal dans le process parent
// on le restaura dans les differentes commandes

int	ft_exec_ast(t_ast *node, t_shell *shell)
{
	if (node->type == NODE_PIPE)
		return (ft_exec_pipe(node, shell));
	if (node->type == NODE_CMD)
		return (ft_exec_cmd(node, shell));
	if (node->type == NODE_SUBSHELL)
		return (ft_exec_subshell(node, shell));
	if (node->type == NODE_AND)
		return (ft_exec_and(node, shell));
	if (node->type == NODE_OR)
		return (ft_exec_or(node, shell));
	if (node->type == NODE_HEREDOC)
		return (ft_exec_heredoc(node, shell));
	if (node->type == NODE_REDIR_IN)
		return (ft_exec_redirect_in(node, shell));
	if (node->type == NODE_REDIR_OUT)
		return (ft_exec_redirect_out(node, shell));
	if (node->type == NODE_REDIR_APPEND)
		return (ft_exec_redirect_append(node, shell));
	return (1);
}
