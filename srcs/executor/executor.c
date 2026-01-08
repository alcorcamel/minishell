#include "executor.h"

void	ft_exec_ast(t_ast *node)
{
	if (node->type == NODE_PIPE)
		ft_exec_pipe(node);
	if (node->type == NODE_CMD)
		ft_exec_cmd(node);
	if (node->type == NODE_SUBSHELL)
		ft_exec_subshell(node);
	if (node->type == NODE_AND)
		ft_exec_and(node);
	if (node->type == NODE_OR)
		ft_exec_or(node);
	if (node->type == NODE_HEREDOC)
		ft_exec_heredoc(node);
	if (node->type == NODE_REDIR_IN)
		ft_exec_redirect_in(node);
	if (node->type == NODE_REDIR_OUT)
		ft_exec_redirect_out(node);
	if (node->type == NODE_REDIR_APPEND)
		ft_exec_redirect_append(node);
}
