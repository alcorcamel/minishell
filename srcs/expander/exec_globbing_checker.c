#include "../../includes/expander.h"

static t_new_args	*ft_argnew(char *value)
{
	t_new_args	*ret;

	ret = (t_new_args *)ft_calloc(1, sizeof(t_new_args));
	if (!ret)
		return (NULL);
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

void	ft_lst_printer(t_new_args **head)
{
	t_new_args	*temp;

	if (!head)
		return ;
	temp = *head;
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}

void	ft_args_printer2(t_ast *n)
{
	t_ast	*temp;
	int		i;

	if (!n)
		return ;
	temp = n;
	i = -1;
	while (temp->args[++i])
	{
		printf("%s\n", temp->args[i]);
	}
}

int	ft_arg_restorer(char *arg)
{
	int	i;
	int	size;

	i = -1;
	if (!arg)
		return (0);
	size = ft_strlen(arg);
	while (++i < size)
	{
		if (arg[i] == '\x1D')
			arg[i] = '*';
	}
	return (1);
}

int	ft_spechar_counter(char *arg)
{
	int	i;
	int	size;
	int	ret;

	i = -1;
	ret = 0;
	if (!arg)
		return (0);
	size = ft_strlen(arg);
	while (++i < size)
	{
		if (arg[i] == '\x1D')
			ret++;
	}
	return (ret);
}

int	ft_arg_lstsize(t_new_args *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_spe_arg_lstsize(t_new_args *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		if (lst->globbed == 1)
			i++;
	}
	return (i);
}

void	ft_arg_add_back(t_new_args **lst, t_new_args *new, int i)
{
	t_new_args	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	if (i == 1)
		new->globbed = 1;
}

int	ft_is_char_match(char c_arg, char c_line)
{
	if (c_arg == c_line)
		return (1);
	return (0);
}

int	ft_valid_star_any(char *line, char *arg)
{
	int	i;
	int	j;
	int found;

	i = 0;
	j = 0;
	found = 0;
	if (arg[0] == '\x1D' && line[0] == '.')
		return (0);
	if (!line[i])
		return (0);
	while (found == 0)
	{
		if (arg[j] == '\x1D')
		{
			while (arg[j] == '\x1D')
				j++;
			if (!arg[j])
				return (1);
			while (line[i] && line[i] != arg[j])
				i++;
			if (!line[i])
				return (0);
			if (ft_valid_star_any(line + i + 1, arg + j - 1))
				return (1);
			if (arg[j] && line[i] != arg[j])
				return (0);
			if (!arg[j] && !line[i])
				return (1);
		}
		else
		{
			while (arg[j] && arg[j] == line[i])
			{
				i++;
				j++;
			}
			if (arg[j] == '\0' && line[i] == '\0')
			{
				found = 1;
				break ;
			}
			if (arg[j] != '\x1D' && arg[j] != line[i])
				return (0);
		}
	}
	return (1);
}

int	ft_star_anywhere(t_new_args **head, char *arg)
{
	DIR*			rep;
	struct dirent	*readfile;
	t_new_args		*tmp;
	int				found;

	found = 0;
	rep = NULL;
	readfile = NULL;
	rep = opendir(".");
	if (!rep)
		return (ft_free_nargs(*head), 0);
	while (1)
	{
		readfile = readdir(rep);
		if (readfile == NULL)
			break ;
		if (readfile->d_name[0] == '.' && arg[0] != '.')
			continue;
		if (ft_valid_star_any(readfile->d_name, arg))
		{
			tmp = ft_argnew(ft_strdup(readfile->d_name));
			found = 1;
			if (!tmp->value)
				return (closedir(rep), ft_free_nargs(*head), 0);
			ft_arg_add_back(head, tmp, 1);
		}
	}
	if (found == 0)
	{
		ft_arg_restorer(arg);
		tmp = ft_argnew(ft_strdup(arg));
		if (!tmp->value)
			return (closedir(rep), ft_free_nargs(*head), free(tmp), 0);
		ft_arg_add_back(head, tmp, 0);
	}
	return (closedir(rep), 1);
}

// int	ft_args_splitter(t_new_args **head, char *arg)
// {
// 	DIR*			rep;
// 	struct dirent	*readfile;

// 	rep = NULL;
// 	if (!arg)
// 		return (ft_free_nargs(*head), 0);
// 	// if (ft_strlen(arg) == 1)
// 	// 	return (ft_only_one_star(head, arg));
// 	// else if (arg[0] == '\x1D' && ft_spechar_counter(arg) == 1)
// 	// 	return (ft_beginning_star(head, arg));
// 	// else if (arg[ft_strlen(arg) - 1] == '\x1D' && ft_spechar_counter(arg) == 1)
// 	// 	return (ft_ending_star(head, arg));
// 	// else
// 	return (ft_star_anywhere(head, arg));
// 	return (1);
// }

int		ft_new_args_maker(t_new_args **head, t_ast *n)
{
	int			size;
	char		**ret;
	int			i;
	t_new_args	*tmp;

	if (!head || !(*head))
		return (0);
	size = ft_arg_lstsize(*head);
	ret = (char **)malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (0);
	i = -1;
	tmp = *head;
	while (tmp && ++i < size)
	{
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	ret[size] = NULL;
	ft_free_args(n->args);
	n->args = NULL;
	n->args = ret;
	return (1);
}

int	ft_valid_star_any_inout(char *line, char *arg)
{
	int	i;
	int	j;
	int found;

	i = 0;
	j = 0;
	found = 0;
	if (arg[0] == '*' && line[0] == '.')
		return (0);
	if (!line[i])
		return (0);
	while (found == 0)
	{
		if (arg[j] == '*')
		{
			while (arg[j] == '*')
				j++;
			if (!arg[j])
				return (1);
			while (line[i] && line[i] != arg[j])
				i++;
			if (!line[i])
				return (0);
			if (ft_valid_star_any_inout(line + i + 1, arg + j - 1))
				return (1);
			if (arg[j] && line[i] != arg[j])
				return (0);
			if (!arg[j] && !line[i])
				return (1);
		}
		else
		{
			while (arg[j] && arg[j] == line[i])
			{
				i++;
				j++;
			}
			if (arg[j] == '\0' && line[i] == '\0')
			{
				found = 1;
				return (1);
				break ;
			}
			if (arg[j] != '*' && arg[j] != line[i])
				return (0);
		}
	}
	return (1);
}

int		ft_inout_globber(t_ast *n)
{
	DIR*			rep;
	struct dirent	*readfile;
	int				found;
	char			*s;

	rep = NULL;
	found = 0;
	s = NULL;
	if (!ft_strchr(n->filename, '*'))
		return (1);
	readfile = NULL;
	rep = opendir(".");
	if (!rep)
		return (0);
	if (!n->filename)
		return (closedir(rep), 0);
	while (1)
	{
		readfile = readdir(rep);
		if (readfile == NULL)
			break ;
		if (readfile->d_name[0] == '.' && n->filename[0] != '.')
			continue;
		if (ft_strchr(n->filename, (int)'*'))
		{
			if (ft_valid_star_any_inout(readfile->d_name, n->filename))
			{
				found++;
				free(s);
				s = ft_strdup(readfile->d_name);
				if (!s)
					return (closedir(rep), 0);
			}
		}
	}
	if (found == 1)
	{
		free(n->filename);
		n->filename = s;
		return (closedir(rep), 1);
	}
	else if (found > 1)
		return (ft_expander_error(n->filename, 1), free(s), closedir(rep), 0);
	return (closedir(rep), 1);
}

void	ft_str_capitalizer(char *str)
{
	size_t	size;
	size_t	i;

	if (!str)
		return ;
	size = ft_strlen(str);
	i = -1;
	while (++i < size)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

int	ft_str_compare(char *s1, char *s2)
{
	char *tmp1;
	char *tmp2;

	if (!s1 || !s2)
		return (0);
	tmp1 = ft_strdup(s1);
	tmp2 = ft_strdup(s2);
	if (!tmp1 || !tmp2)
		return (0);
	ft_str_capitalizer(tmp1);
	ft_str_capitalizer(tmp2);
	return (strcmp(tmp1, tmp2));
}

void	ft_sublist_sorter(t_new_args **head, t_ast *n)
{
	int			i;
	t_new_args	*tmp;
	t_new_args	*new_head;
	char		*bkp;

	if (!head || !(*head))
		return ;
	i = -1;
	tmp = *head;
	while (tmp && tmp->globbed == 0)
		tmp = tmp->next;
	new_head = tmp;
	while (new_head->next && new_head->next->globbed == 1)
	{
		tmp = new_head->next;
		while (tmp)
		{
			if (tmp && ft_str_compare(new_head->value, tmp->value) > 0 && tmp->globbed == 1)
			{
				bkp = tmp->value;
				tmp->value = new_head->value;
				new_head->value = bkp;
			}
			tmp = tmp->next;
		}
		new_head = new_head->next;
	}
}

int		ft_args_handler(t_ast *n)
{
	int			i;
	t_new_args	*tmp;
	char		**ret;
	t_new_args	*head;
	int			found;

	i = -1;
	found = 0;
	ret = NULL;
	head = NULL;
	n->globber = head;
	// if (n->args[0] && n->args[0][0] == '\x1D')
	// 	ft_arg_restorer(n->args[0]);
	while (n->args[++i])
	{
		if (ft_strchr(n->args[i], (int)'\x1D'))
		{
			found = 1;
			ft_star_anywhere(&head, n->args[i]);
		}
		else
		{
			tmp = ft_argnew(ft_strdup(n->args[i]));
			if (!tmp->value)
				return (0);
			ft_arg_add_back(&head, tmp, 0);
		}
	}
	if (found)
		ft_sublist_sorter(&head, n);
	ft_new_args_maker(&head, n);
	//ft_args_sorter(n);
	ft_free_nargs(head);
	return (1);
}
