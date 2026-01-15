
#include "lexer.h"

void	ft_free(void **p);
char	*ft_strjoin_sep(char *s1, char *s2, char sep);
int		ft_str_is_space(char *str);

int	ft_get_index_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
	}
	return (-1);
}

void	ft_free_all_split_val(char ***split_val)
{
	char	**free_val;
	int		i;

	if (!split_val)
		return ((void)0);
	free_val = *split_val;
	if (!free_val)
		return ((void)0);
	i = 0;
	while (free_val[i])
	{
		ft_free((void **)&free_val[i]);
		i++;
	}
	ft_free((void **)&free_val);
}

int	ft_access(char **path_params, t_ast p, char ***split_val, t_bool bool)
{
	int		acs_val;
	char	*path;

	path = *path_params;
	if (!path)
		return (0);
	if (ft_strchr(path, '/') == NULL)
		return (0);
	acs_val = access(path, X_OK);
	if (acs_val == 0)
		return (1);
	return (0);
}

int	ft_access_in_rep(char **path_params, t_ast p, char ***split_val)
{
	int		acs_val;
	char	*path;
	char	*check;

	path = *path_params;
	if (!path)
		return (0);
	check = ft_strchr(path, '.');
	if (check == NULL || *(check + 1) != '/')
		return (0);
	acs_val = access(path, X_OK);
	if (acs_val == 0)
		return (1);
	if (errno == EACCES)
	{
		perror(path);
		ft_free_all_split_val(split_val);
		// ft_free_all_node
		exit(126);
	}
	return (0);
}

char	*ft_try_paths(char ***split_val, char *cmd_name, t_ast p)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while ((*split_val)[++i])
	{
		path = ft_strjoin_sep((*split_val)[i], cmd_name, '/');
		if (!path)
		{
			ft_free_all_split_val(split_val);
			// ft_free_all_node
			exit(1);
		}
		if (ft_access(&path, p, split_val, TRUE))
			return (ft_free_all_split_val(split_val), path);
		ft_free((void **)&path);
	}
	return (ft_free_all_split_val(split_val), NULL);
}

char	*ft_get_path(t_ast *node, t_shell *shell)
{
	char	*path;
	char	**split_val;
	int		index;
	char	*cmd;

	cmd = node->args[0];
	if (!cmd)
		return (NULL);
	if (ft_strlen(cmd) == 0 || ft_str_is_space(cmd))
		return (ft_strdup(cmd));
	if (ft_access_in_rep(&(cmd), *node, NULL))
		return (ft_strdup(cmd));
	index = ft_get_index_path(shell->envp);
	if (index == -1)
		return (NULL);
	split_val = ft_split(shell->envp[index] + 5, ':');
	if (!split_val)
		return (NULL);
	path = ft_try_paths(&split_val, cmd, *node);
	if (errno == EACCES)
	{
		perror(path);
		ft_free((void **)&path);
		ft_free_all_split_val(&split_val);
		// ft_free_all_node
		exit(126);
	}
	if (!path)
		return (ft_strdup(cmd));
	return (path);
}
