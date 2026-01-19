#include "../../includes/env.h"

char	*ft_get_key_from_var_envp(char *var_envp)
{
	int		i;
	char	*key;

	i = 0;
	while (var_envp[i] && var_envp[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (var_envp[i] && var_envp[i] != '=')
	{
		key[i] = var_envp[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_bool	ft_get_value_from_var_envp(char *var_envp, char **value)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	while (var_envp[i] && var_envp[i] != '=')
		i++;
	if (var_envp[i] != '=')
		return (*value = NULL, TRUE);
	j = i++;
	while (var_envp[i])
		i++;
	val = (char *)malloc(sizeof(char) * (i - j));
	if (!val)
		return (*value = NULL, FALSE);
	i = 0;
	while (var_envp[++j])
	{
		if (var_envp[j] != '"' && var_envp[j] != '\'')
			val[i++] = var_envp[j];
	}
	val[i] = '\0';
	*value = val;
	return (TRUE);
}

t_vars	*ft_create_new_vars(char *var_envp, t_bool is_exported)
{
	char	*key;
	char	*value;
	int		i;
	int		j;
	t_vars	*new;

	key = NULL;
	value = NULL;
	new = (t_vars *)malloc(sizeof(t_vars));
	if (!new)
		return (NULL);
	new->is_exported = is_exported;
	new->next = NULL;
	key = ft_get_key_from_var_envp(var_envp);
	if (!key)
		return (ft_free((void **)&new), NULL);
	new->key = key;
	if (ft_get_value_from_var_envp(var_envp, &value) == FALSE)
		return (ft_free((void **)&new), ft_free((void **)&key), NULL);
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
		if (ft_strncmp(key, iterator->key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(iterator->key))
			return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}

void	ft_free_vars(t_vars **var)
{
	ft_free((void **)&(*var)->key);
	ft_free((void **)&(*var)->value);
	ft_free((void **)&(*var));
}

t_bool	ft_del_vars(t_vars *del, t_shell *shell)
{
	t_vars	*iterator;
	t_vars	*prev;

	iterator = shell->vars;
	prev = NULL;
	if (del == NULL || shell->vars == NULL)
		return (TRUE);
	while (iterator)
	{
		if (ft_strncmp(iterator->key, del->key, ft_strlen(del->key)) == 0
			&& ft_strlen(del->key) == ft_strlen(iterator->key))
		{
			if (prev)
				prev->next = iterator->next;
			else
				shell->vars = iterator->next;
			ft_free_vars(&iterator);
			return (TRUE);
		}
		prev = iterator;
		iterator = iterator->next;
	}
	return (FALSE);
}

int	ft_print_envp(t_shell *shell, t_bool is_aff_export)
{
	t_vars	*iterator;

	iterator = shell->vars;
	while (iterator)
	{
		if (iterator->is_exported == TRUE)
		{
			if (is_aff_export == TRUE)
				ft_printf("export %s", iterator->key);
			else
				ft_printf("%s", iterator->key);
			if (iterator->value)
			{
				if (is_aff_export == TRUE)
					ft_printf("=\"%s\"\n", iterator->value);
				else
					ft_printf("=%s\n", iterator->value);
			}
			else
				ft_printf("\n");
		}
		iterator = iterator->next;
	}
	return (0);
}

void	ft_free_all_envp(char ***envp)
{
	int	i;

	if (!envp || *envp)
		return ((void)0);
	i = -1;
	while (*envp[++i])
	{
		ft_free((void **)&(*envp[i]));
	}
	ft_free((void **)&(*envp));
}

char	*ft_make_envp_line(t_vars *var)
{
	char	*line;
	int		j;
	int		i;

	if (!var)
		return (NULL);
	j = ft_strlen(var->key) + ft_strlen(var->value) + 2;
	line = (char *)ft_calloc(j, sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (var->key[++i] != '\0')
		line[i] = var->key[i];
	if (!var->value)
		return (line[i] = '\0', line);
	line[i++] = '=';
	j = -1;
	while (var->value[++j])
		line[i++] = var->value[j];
	line[i] = '\0';
	return (line);
}

char	**ft_make_envp(t_vars *vars)
{
	int		i;
	t_vars	*iterator;
	char	**envp;

	if (!vars)
		return (NULL);
	i = 0;
	iterator = vars;
	while (iterator)
	{
		i++;
		iterator = iterator->next;
	}
	envp = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	envp[i] = NULL;
	i = 0;
	iterator = vars;
	while (iterator)
	{
		envp[i] = ft_make_envp_line(iterator);
		if (!envp[i++])
			return (ft_free_all_envp(&envp), NULL);
		iterator = iterator->next;
	}
	envp[i] = NULL;
	return (envp);
}
