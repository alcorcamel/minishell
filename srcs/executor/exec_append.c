#include "../../includes/base.h"

int		ft_exec_append(t_ast *node, t_shell *shell)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_throw_error(node->filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (ft_exec_ast(node->left, shell));
}
