#include "../../includes/expander.h"

int	ft_inout_globber3(t_ast *n, int *found, char **s)
{
	if (*found == 1)
	{
		free(n->filename);
		n->filename = *s;
		*s = NULL;
		return (1);
	}
	else if (*found > 1)
		return (ft_expander_error(n->filename, 1), free(*s), *s = NULL, 0);
	return (free(*s), *s = NULL, 1);
}

int	ft_inout_globber2(t_ast *n, DIR **rep, struct dirent **rf, int *found)
{
	char	*s;

	s = NULL;
	if (!n->filename)
		return (0);
	while (1)
	{
		*rf = readdir(*rep);
		if (*rf == NULL)
			break ;
		if ((*rf)->d_name[0] == '.' && n->filename[0] != '.')
			continue ;
		if (ft_valid_star_any_inout((*rf)->d_name, n->filename))
		{
			(*found)++;
			free(s);
			s = ft_strdup((*rf)->d_name);
			if (!s)
				return (0);
		}
	}
	return (ft_inout_globber3(n, found, &s));
}

int	ft_inout_globber(t_ast *n)
{
	DIR				*rep;
	struct dirent	*readfile;
	int				found;
	int				ret;

	rep = NULL;
	found = 0;
	if (!n || !n->filename)
		return (0);
	if (!ft_strchr(n->filename, '*'))
		return (1);
	readfile = NULL;
	rep = opendir(".");
	if (!rep)
		return (perror("minishell: opendir"), 0);
	readfile = NULL;
	ret = ft_inout_globber2(n, &rep, &readfile, &found);
	closedir(rep);
	return (ret);
}
