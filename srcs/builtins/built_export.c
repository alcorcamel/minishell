#include "../../includes/builtins.h"

void	ft_print_err_id_invalide(char *err)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd("<< ", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd(" >>", STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd("identifiant non valable", STDERR_FILENO);
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
	int		len;
	int		i;
	int		j;
	char	*tmp;

	key = ft_get_key_from_var_envp(arg);
	new_value = NULL;
	if(!key)
		return ((void)0);
	search_vars = ft_find_vars(key, shell);
	ft_free((void **)&key);
	if (!search_vars)
	{
		search_vars = ft_create_new_vars(arg, TRUE);
		ft_add_vars(shell, search_vars);
		return ((void)0);
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		new_value = NULL;
	else
	{
		j = i++;
		len = 0;
		while (arg[i])
		{
			if (arg[i] != '"' && arg[i] != '\'')
				len++;
			i++;
		}
		new_value = (char *)malloc(sizeof(char) * (len + 1));
		if (!new_value)
			return ((void)0);
		i = 0;
		while (arg[++j])
			if (arg[j] != '"' && arg[j] != '\'')
				new_value[i++] = arg[j];
		new_value[i] = '\0';
	}
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
		return (ft_print_envp(shell));
	i = 1;
	while (args[i])
	{
		if (ft_is_valid_args_export(args[i]) == TRUE)
			ft_add_or_replace_vars(args[i], shell);
		i++;
	}
	return (0);
}

