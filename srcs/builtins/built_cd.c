#include "../../includes/builtins.h"

int	ft_print_err_cd(void)
{
	ft_putstr_fd("minishield: cd: too many arguments\n", STDERR_FILENO);
	return (1);
}

int	ft_print_err_cd_no_directory(char *dir)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishield: cd: ", STDERR_FILENO);
		if (dir)
			ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (ft_is_directory(dir) == FALSE)
	{
		ft_putstr_fd("minishield: cd: ", STDERR_FILENO);
		if (dir)
			ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishield: cd: ", STDERR_FILENO);
		if (dir)
			ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	return (1);
}

t_bool	ft_assign_path(char **args, t_shell *shell, char **path)
{
	t_vars	*var;

	if (!args[1])
	{
		var = ft_find_vars("HOME", shell);
		if (var && var->value)
		{
			*path = ft_strdup(var->value);
			if (!path)
				return (FALSE);
		}
		else
			*path = NULL;
	}
	else
		*path = ft_strdup(args[1]);
	return (TRUE);
}

t_bool	ft_check_sign(char **path, t_shell *shell)
{
	t_vars	*var;
	char	*new_path;

	var = NULL;
	new_path = NULL;
	if (ft_strncmp(*path, "-", ft_strlen(*path)) == 0 && ft_strlen(*path) == 1)
	{
		var = ft_find_vars("OLDPWD", shell);
		if (var && var->value)
		{
			new_path = ft_strdup(var->value);
			if (!new_path)
				return (FALSE);
		}
		ft_free((void **)path);
		*path = new_path;
	}
	return (TRUE);
}

void	ft_assign_new_pwd(t_shell *shell)
{
	char	*var_envp;
	char	*cwd;
	t_vars	*var;
	char	*tmp;

	var = ft_find_vars("PWD", shell);
	if (var)
	{
		tmp = var->value;
		var->value = getcwd(NULL, 0);
		ft_free((void **)&tmp);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		var = ft_create_new_vars("PWD", TRUE);
		var->value = cwd;
		ft_add_vars(shell, var);
	}
}

void	ft_assign_new_oldpwd(t_shell *shell, char *last_path)
{
	t_vars	*var;
	char	*tmp;

	var = ft_find_vars("OLDPWD", shell);
	if (var)
	{
		tmp = var->value;
		if (last_path)
		{
			var->value = ft_strdup(last_path);
			ft_free((void **)&tmp);
		}
	}
	else
	{
		var = ft_create_new_vars("OLDPWD", TRUE);
		if (last_path)
			var->value = ft_strdup(last_path);
		else
			var->value = NULL;
		ft_add_vars(shell, var);
	}
}

int	ft_cd(char **args, t_shell *shell)
{
	t_vars	*var;
	char	*path;
	char	*tmp;
	char	*last_path;

	last_path = NULL;
	path = NULL;
	if (args[1] && args[2])
		return (ft_print_err_cd());
	if (ft_assign_path(args, shell, &path) == FALSE)
		return (1);
	if (!path)
		return (ft_putstr_fd("minishield: cd: << HOME >> not defined", \
			STDERR_FILENO), 1);
	if (ft_check_sign(&path, shell) == FALSE)
		return (1);
	if (!path)
		return (ft_putstr_fd("minishield: cd: << OLDPWD >> not defined", \
			STDERR_FILENO), 1);
	last_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (ft_print_err_cd_no_directory(args[1]));
	return (ft_assign_new_pwd(shell), ft_assign_new_oldpwd(shell, last_path),
		ft_free((void **)&path), ft_free((void **)&last_path), 0);
}
