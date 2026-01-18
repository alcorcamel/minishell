#include "../../includes/builtins.h"

static int	ft_print_err_pwd(void)
{
	ft_putstr_fd("pwd : too many arguments\n", STDERR_FILENO);
	return (1);
}

int	ft_pwd(char **arg)
{
	char	*cwd;

	if (arg[1])
		return (ft_print_err_pwd());
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

