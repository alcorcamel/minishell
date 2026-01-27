#include "../../includes/env.h"

static t_bool	ft_add_vars_emergency(char *cwd, t_shell *shell)
{
	t_vars	*var;

	var = ft_create_new_vars(cwd, TRUE);
	if (!var)
		return (FALSE);
	ft_add_vars(shell, var);
	var = ft_create_new_vars("OLDPWD", TRUE);
	if (!var)
		return (ft_free_all_env(&shell->vars), FALSE);
	ft_add_vars(shell, var);
	if (!var)
		return (ft_free_all_env(&shell->vars), FALSE);
	var = ft_create_new_vars("_=/usr/bin/env", TRUE);
	if (!var)
		return (ft_free_all_env(&shell->vars), FALSE);
	ft_add_vars(shell, var);
	var = ft_create_new_vars("SHLVL=1", TRUE);
	if (!var)
		return (ft_free_all_env(&shell->vars), FALSE);
	ft_add_vars(shell, var);
	return (TRUE);
}

static t_bool	ft_create_path_emergency(t_shell *shell)
{
	t_vars	*var;
	char	*cwd;
	char	*tmp;

	var = ft_create_new_vars("PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin:\
/snap/bin:/var/lib/flatpak/exports/bin", FALSE);
	if (!var)
		return (FALSE);
	ft_add_vars(shell, var);
	cwd = getcwd(NULL, 0);
	tmp = cwd;
	if (!tmp)
		cwd = ft_strdup("PWD");
	else
		cwd = ft_strjoin("PWD=", tmp);
	if (!cwd)
		return (ft_free((void **)&tmp), FALSE);
	ft_free((void **)&tmp);
	if (ft_add_vars_emergency(cwd, shell) == FALSE)
		return (ft_free((void **)&cwd), FALSE);
	return (TRUE);
}

static t_bool	ft_increment_shlvl(t_shell *shell)
{
	t_vars	*var;
	int		shell_lvl;
	char	*tmp;

	tmp = NULL;
	var = ft_find_vars("SHLVL", shell);
	if (!var)
		return (TRUE);
	shell_lvl = ft_atoi(var->value);
	if (shell_lvl < INT_MAX)
		shell_lvl++;
	else
		shell_lvl = 0;
	tmp = var->value;
	var->value = ft_itoa(shell_lvl);
	if (!var->value)
		return (FALSE);
	ft_free((void **)&tmp);
	return (TRUE);
}

t_bool	ft_cpy_enpv(char **envp, t_shell *shell)
{
	t_vars	*new_vars;
	int		i;

	new_vars = NULL;
	i = 0;
	while (envp && envp[i] != NULL)
	{
		new_vars = ft_create_new_vars(envp[i], TRUE);
		if (!new_vars)
			return (FALSE);
		ft_add_vars(shell, new_vars);
		i++;
	}
	if (ft_increment_shlvl(shell) == FALSE)
		return (FALSE);
	if (ft_find_vars("PATH", shell) == NULL)
		if (ft_create_path_emergency(shell) == FALSE)
			return (ft_free_all_env(&(shell->vars)), FALSE);
	return (TRUE);
}

