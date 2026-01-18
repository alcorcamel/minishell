#include "../../includes/builtins.h"

//Fonction	Utilité
// chdir	changer de dossier
// getcwd	récupérer le chemin courant
// perror	afficher erreur système
// access	vérifier existence / permissions
// stat		vérifier que c’est un dossier

int	ft_print_err_cd(void)
{
	ft_putstr_fd("minishield: cd: trop d'arguments\n", STDERR_FILENO);
	return (1);
}

int	ft_print_err_cd_no_directory(char *dir)
{
	ft_putstr_fd("minishield: cd: ", STDERR_FILENO);
	if (dir)
		ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": Aucun fichier ou dossier de ce nom\n", STDERR_FILENO);
	return (1);
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
	if (!args[1])
	{
		var = ft_find_vars("HOME", shell);
		if (var)
			path = ft_strdup(var->value);
		else
			path = NULL;
	}
	else
		path = ft_strdup(args[1]);
	if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0 && ft_strlen(args[1]) == 1)
	{
		var = ft_find_vars("OLDPWD", shell);
		if (var)
			path = ft_strdup(var->value);
		if (!path)
			return (ft_putstr_fd("minishield: cd: << OLDPWD >> non defini", STDERR_FILENO), 1);
	}
	if (ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0 && ft_strlen(args[1]) == 1)
	{
		var = ft_find_vars("HOME", shell);
		if (var)
			path = ft_strdup(var->value);
		if (!path)
			return (ft_putstr_fd("minishield: cd: << HOME >> non defini", STDERR_FILENO), 1);
	}
	if (!path)
		return (ft_putstr_fd("minishield: cd: << HOME >> non defini", STDERR_FILENO), 1);
	if (chdir(path) == -1)
		return (ft_print_err_cd_no_directory(args[1]));
	var = ft_find_vars("PWD", shell);
	if (var)
	{
		tmp = var->value;
		if (tmp)
			last_path = ft_strdup(var->value);
		var->value = getcwd(NULL, 0);
		ft_free((void **)&tmp);
	}
	else
	{
		char *var_envp;
		char *cwd;

		cwd = getcwd(NULL, 0);
		last_path = ft_strdup(cwd);
		ft_free((void **)&cwd);
		var = ft_create_new_vars("PWD", TRUE);
		var->value = ft_strdup(path);
		ft_add_vars(shell, var);
	}
	var = ft_find_vars("OLDPWD", shell);
	if (var)
	{
		tmp = var->value;
		var->value = ft_strdup(last_path);
		ft_free((void **)&tmp);
	}
	else
	{
		var = ft_create_new_vars("OLDPWD", TRUE);
		var->value = ft_strdup(last_path);
		ft_add_vars(shell, var);
	}
	ft_free((void **)&path);
	ft_free((void **)&last_path);
	return (0);
}
