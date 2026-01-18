#include "../../includes/builtins.h"

void	ft_print_err_id_invalide(char *err)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd("<< ", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd(" >>", STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd("identifiant non valable\n", STDERR_FILENO);
}

static t_bool	ft_is_valid_args_export(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) != 1 && arg[i] != '_')
		return (ft_print_err_id_invalide(arg), FALSE);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (ft_print_err_id_invalide(arg), FALSE);
		i++;
	}
	if (!arg[i])
		return (TRUE);
	while (arg[++i])
	{
		if (ft_isascii(arg[i]) == 0)
			return (ft_print_err_id_invalide(arg), FALSE);
	}
	return (TRUE);
}

void	ft_add_or_replace_vars(char *arg, t_shell *shell)
{
	char	*key;
	t_vars	*search_vars;
	char	*new_value;
	char	*tmp;

	key = ft_get_key_from_var_envp(arg);
	new_value = NULL;
	if (!key)
		return ((void)0);
	search_vars = ft_find_vars(key, shell);
	ft_free((void **)&key);
	if (!search_vars)
	{
		search_vars = ft_create_new_vars(arg, TRUE);
		ft_add_vars(shell, search_vars);
		return ((void)0);
	}
	if (ft_get_value_from_var_envp(arg, &new_value) == FALSE)
		return ((void)0);
	if (new_value != NULL)
	{
		tmp = search_vars->value;
		search_vars->value = new_value;
		ft_free((void **)&tmp);
	}
}

int	ft_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
		return (ft_print_envp(shell, TRUE));
	i = 1;
	while (args[i])
	{
		if (ft_is_valid_args_export(args[i]) == TRUE)
			ft_add_or_replace_vars(args[i], shell);
		i++;
	}
	return (0);
}

