#include "../../includes/expander.h"

int	ft_star_any3(t_new_args **head, char *arg)
{
	char		*copy;
	t_new_args	*tmp;

	copy = ft_strdup(arg);
	if (!copy)
		return (0);
	ft_arg_restorer_bis(copy);
	tmp = ft_argnew(copy);
	if (!tmp)
		return (free(copy), 0);
	ft_arg_add_back(head, tmp, 0);
	return (1);
}

int	ft_star_any2(t_new_args **head, struct dirent *readfile)
{
	char			*s;
	t_new_args		*tmp;

	s = ft_strdup(readfile->d_name);
	if (!s)
		return (0);
	tmp = ft_argnew(s);
	if (!tmp)
		return (free(s), 0);
	ft_arg_add_back(head, tmp, 1);
	return (1);
}

int	ft_star_anywhere2(DIR **rep, char *arg, t_new_args **head, int *found)
{
	struct dirent	*readfile;

	readfile = readdir(*rep);
	while (readfile)
	{
		if (readfile->d_name[0] == '.' && arg[0] != '.')
		{
			readfile = readdir(*rep);
			continue ;
		}
		if (ft_valid_star_any(readfile->d_name, arg))
		{
			*found = 1;
			if (!ft_star_any2(head, readfile))
				return (closedir(*rep), 0);
		}
		readfile = readdir(*rep);
	}
	return (1);
}

int	ft_star_anywhere(t_new_args **head, char *arg)
{
	DIR				*rep;
	struct dirent	*readfile;
	int				found;

	rep = opendir(".");
	if (!rep)
		return (perror("minishell: opendir"), 0);
	found = 0;
	if (!ft_star_anywhere2(&rep, arg, head, &found))
		return (0);
	if (!found)
	{
		if (!ft_star_any3(head, arg))
			return (closedir(rep), 0);
	}
	return (closedir(rep), 1);
}

int	ft_new_args_maker(t_new_args **head, t_ast *n)
{
	int			size;
	char		**ret;
	int			i;
	t_new_args	*tmp;

	if (!head || !(*head))
		return (ft_free_args(n->args), n->args = NULL, 1);
	size = ft_arg_lstsize(*head);
	ret = (char **)malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (0);
	i = -1;
	tmp = *head;
	while (tmp && ++i < size)
	{
		ret[i] = ft_strdup(tmp->value);
		if (!ret[i])
			return (ret[i] = NULL, ft_free_args(ret), 0);
		tmp = tmp->next;
	}
	ret[size] = NULL;
	ft_free_args(n->args);
	n->args = NULL;
	n->args = ret;
	return (1);
}
