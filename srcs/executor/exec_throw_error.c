
#include "../../includes/executor.h"

int	ft_throw_error(char *err_p)
{
	perror(err_p);
	if (errno == EACCES || errno == ENOEXEC)
		return (126);
	if (errno == ENOENT)
		return (127);
	return (1);
}

int	ft_throw_error_cmd_not_found(char *err_p)
{
	ft_putstr_fd(err_p, STDOUT_FILENO);
	ft_putstr_fd(": command not found", STDOUT_FILENO);
	return (127);
}
