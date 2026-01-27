#include "../../includes/builtins.h"

int	ft_pwd(char **arg)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_perror("pwd: error retrieving current directory: getcwd: cannot access\
parent directories");
		return (1);
	}
	ft_printf("%s\n", cwd);
	ft_free((void **)&cwd);
	return (0);
}

