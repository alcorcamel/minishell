#include "../../includes/env.h"

t_vars	*ft_create_new_vars(char *var_envp, t_bool is_exported)
{
	char	*key;
	char	*value;
	int		i;
	int		j;
	t_vars	*new;

	i = 0;
	key = NULL;
	value = NULL;
	new = (t_vars *)malloc(sizeof(t_vars));
	if (!new)
		return (NULL);
	new->is_exported = is_exported;
	new->next = NULL;
	while (var_envp[i] && var_envp[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (ft_free((void **)&new), NULL);
	i = 0;
	while (var_envp[i] && var_envp[i] != '=')
	{
		key[i] = var_envp[i];
		i++;
	}
	key[i] = '\0';
	new->key = key;
	if (var_envp[i] != '=')
		return (new->value = NULL, new);
	j = i++;
	while (var_envp[i])
		i++;
	value = (char *)malloc(sizeof(char) * (i - j));
	if (!value)
		return (ft_free((void **)&new), ft_free((void **)&key), NULL);
	i = 0;
	while (var_envp[++j])
		value[i++] = var_envp[j];
	value[i] = '\0';
	new->value = value;
	return (new);
}

void	ft_add_vars(t_shell *shell, t_vars *vars)
{
	t_vars	*iterator;

	iterator = shell->vars;
	if (!iterator)
		return (shell->vars = vars, (void)0);
	while (iterator->next != NULL)
		iterator = iterator->next;
	iterator->next = vars;
}

t_bool	ft_cpy_enpv(char **envp, t_shell *shell)
{
	t_vars	*new_vars;
	int		i;

	if (!envp)
		return (TRUE);
	new_vars = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_vars = ft_create_new_vars(envp[i], TRUE);
		if (!new_vars)
			return (FALSE);
		ft_add_vars(shell, new_vars);
		i++;
	}
	return (TRUE);
}

t_vars	*ft_find_vars(char *key, t_shell *shell)
{
	t_vars	*iterator;

	iterator = shell->vars;
	while (iterator != NULL)
	{
		if (ft_strncmp(key, iterator->key, ft_strlen(key)) == 0)
			return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}

int	ft_print_envp(t_shell *shell)
{
	t_vars	*iterator;

	iterator = shell->vars;
	while (iterator)
	{
		if (iterator->is_exported == TRUE)
			ft_printf("%s=\"%s\"\n", iterator->key, iterator->value);
		iterator = iterator->next;
	}
	return (0);
}
