#include "../../includes/executor.h"

int		ft_exec_here_doc(t_ast *node, t_shell *shell)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
		return (ft_throw_error(node->filename));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (ft_exec_ast(node->left, shell));
}