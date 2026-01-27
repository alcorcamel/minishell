#include "../../includes/env.h"

static char	*ft_make_envp_line(t_vars *var)
{
	char	*line;
	int		j;
	int		i;

	if (!var)
		return (NULL);
	if (var->key && var->value)
		j = ft_strlen(var->key) + ft_strlen(var->value) + 2;
	else
		j = ft_strlen(var->key) + 1;
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

static int	ft_calcul_len(t_vars *vars)
{
	int		i;
	t_vars	*iterator;

	i = 0;
	iterator = vars;
	while (iterator)
	{
		i++;
		iterator = iterator->next;
	}
	return (i);
}

char	**ft_make_envp(t_vars *vars)
{
	int		i;
	t_vars	*iterator;
	char	**envp;

	if (!vars)
		return (NULL);
	i = ft_calcul_len(vars);
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
	return (envp[i] = NULL, envp);
}
