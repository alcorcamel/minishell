#include "executor.h"

//manque a gerer les erreurs de open et de dup2 au cas ou ca foire

int		ft_exec_redirect_in(t_ast *node, t_shell *shell)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
		ft_throw_error(node->filename);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (ft_exec_ast(node->left, shell));
}

int		ft_exec_redirect_out(t_ast *node, t_shell *shell)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_throw_error(node->filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (ft_exec_ast(node->left, shell));
}
