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

void	ft_arg_add_back(t_new_args **lst, t_new_args *new)
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
		return (0);
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
				return (0);
			ft_arg_add_back(head, tmp);
		}
	}
	if (found == 0)
	{
		ft_arg_restorer(arg);
		tmp = ft_argnew(ft_strdup(arg));
		if (!tmp->value)
			return (closedir(rep), 0);
		ft_arg_add_back(head, tmp);
	}
	closedir(rep);
	return (1);
}

int	ft_args_splitter(t_new_args **head, char *arg)
{
	DIR*			rep;
	struct dirent	*readfile;

	rep = NULL;
	if (!arg)
		return (0);
	// if (ft_strlen(arg) == 1)
	// 	return (ft_only_one_star(head, arg));
	// else if (arg[0] == '\x1D' && ft_spechar_counter(arg) == 1)
	// 	return (ft_beginning_star(head, arg));
	// else if (arg[ft_strlen(arg) - 1] == '\x1D' && ft_spechar_counter(arg) == 1)
	// 	return (ft_ending_star(head, arg));
	// else
		return (ft_star_anywhere(head, arg));
	return (1);
}
int		ft_new_args_maker(t_new_args **head, t_ast *n)
{
	int			size;
	char		**ret;
	int			i;
	t_new_args	*tmp;

	if (!head || !(*head))
		return (0);
	size = ft_arg_lstsize(*head);
	// ret = NULL;
	ret = (char **)malloc((size + 1) * sizeof(char *));
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
// FREE TTE LA LISTE!!!
// TESTER SI REDIR essaie in/out un dossier
// bash: */: ambiguous redirect
// DIR *d;
// d = opendir(path);
// if (d)
// 	OK!!

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
	char 			*bkp;

	rep = NULL;
	found = 0;
	s = NULL;
	readfile = NULL;
	rep = opendir(".");
	if (!rep)
		return (0);
	if (!n->filename)
		return (closedir(rep), 0);
	bkp = ft_strdup(n->filename);
	while (1)
	{
		readfile = readdir(rep);
		if (readfile == NULL)
			break ;
		if (ft_strchr(n->filename, (int)'*'))
		{
			if (ft_valid_star_any_inout(readfile->d_name, n->filename))
			{
				found++;
				free(s);
				s = ft_strdup(readfile->d_name);
				free(n->filename);
				n->filename = s;
			}
		}
	}
	if (found > 1)
	{
		free(n->filename);
		n->filename = ft_strdup(bkp);
		printf("++%s\n", n->filename);
		ft_expander_error(bkp, 1);
		free(bkp);
		return (closedir(rep), 0);
	}
	return (closedir(rep), 1);
}

int		ft_args_handler(t_ast *n)
{
	int			i;
	t_new_args	*tmp;
	char		**ret;
	t_new_args	*head;

	i = -1;
	ret = NULL;
	head = NULL;
	n->globber = head;
	// if (n->args[0] && n->args[0][0] == '\x1D')
	// 	ft_arg_restorer(n->args[0]);
	while (n->args[++i])
	{
		if (ft_strchr(n->args[i], (int)'\x1D'))
			ft_args_splitter(&head, n->args[i]);
		else
		{
			tmp = ft_argnew(ft_strdup(n->args[i]));
			if (!tmp->value)
				return (0);
			ft_arg_add_back(&head, tmp);
		}
	}
	ft_new_args_maker(&head, n);
	return (1);
}

