
#include "../../includes/executor.h"

int	ft_throw_error(char *err_p)
{
	perror(err_p);
	if (errno == EACCES || errno == ENOEXEC)
		return (126);
	if (errno == ENOENT)
		return (127);
}
