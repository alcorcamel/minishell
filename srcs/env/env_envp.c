/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:20:19 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:20:19 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (key[i] = '\0', key);
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
		if (var_envp[j] != '"')
			val[i++] = var_envp[j];
	}
	return (val[i] = '\0', *value = val, TRUE);
}

t_vars	*ft_create_new_vars(char *var_envp, t_bool is_exported)
{
	char	*key;
	char	*value;
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
	return (new->value = value, new);
}

void	ft_add_vars(t_shell *shell, t_vars *vars)
{
	t_vars	*current;

	if (!vars)
		return ((void)0);
	if (!shell->vars || ft_strncmp(vars->key, shell->vars->key,
			ft_strlen(vars->key) + 1) < 0)
	{
		vars->next = shell->vars;
		shell->vars = vars;
		return ((void)0);
	}
	current = shell->vars;
	while (current->next && ft_strncmp(vars->key, current->next->key,
			ft_strlen(vars->key) + 1) > 0)
		current = current->next;
	vars->next = current->next;
	current->next = vars;
}
