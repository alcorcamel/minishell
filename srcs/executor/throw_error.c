#include "executor.h"

void	ft_throw_error(char *err_p)
{
	perror(err_p);
	if (errno == EACCES || errno == ENOEXEC)
		exit(126);
	if (errno == ENOENT)
		exit(127);
}
