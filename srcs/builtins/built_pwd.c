#include "../../includes/builtins.h"

int	ft_pwd(char **arg)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	ft_free((void **)&cwd);
	return (0);
}

