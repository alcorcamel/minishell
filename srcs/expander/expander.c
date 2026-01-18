
#include "../../includes/expander.h"

static int	ft_is_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| c == '_')
		return (1);
	return (0);
}

static int	ft_is_var_char(char c)
{
	if (ft_is_var_start(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static int	ft_var_name_len(char *s)
{
	int	i;

	if (!s || !ft_is_var_start(s[0]))
		return (0);
	i = 0;
	while (s[i] && ft_is_var_char(s[i]))
		i++;
	return (i);
}

static t_vars	*ft_varsnew(char *key, char *value)
{
	t_vars	*ret;

	ret = (t_vars *)malloc(sizeof(t_vars));
	if (!ret)
		return (NULL);
	ret->key = key;
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

// static char	*ft_envp_finder(char **envp, char *s)
// {
// 	int		i;
// 	char	*str;
// 	char	*ret;

// 	i = -1;
// 	str = ft_strjoin(s, "=");
// 	if (!str)
// 		return (NULL);
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
// 		{
// 			ret = ft_strdup(ft_strchr(envp[i], '=') + 1);
// 			if (!ret)
// 				return (free(str), NULL);
// 			return (free(str), ret);
// 		}
// 	}
// 	free(str);
// 	return (NULL);
// }

static void	ft_varsadd_back(t_vars **lst, t_vars *newvars)
{
	t_vars	*tmp;

	if (!lst || !newvars)
		return ;
	if (!*lst)
	{
		*lst = newvars;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newvars;
}

static int	ft_is_limiter(char *line, char *limiter)
{
	size_t	len;

	if (!line || !limiter)
		return (0);
	len = ft_strlen(limiter);
	return (ft_strncmp(line, limiter, len) == 0
		&& line[len] == '\n'
		&& line[len + 1] == '\0');
}

static void	ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

static void	ft_join_segs_until_sep_helper(t_seg *temp, size_t *size)
{
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->text)
			*size += ft_strlen(temp->text);
		temp = temp->next;
	}
}

static char	*ft_join_segs_until_sep(t_seg *seg)
{
	size_t	size;
	size_t	i;
	t_seg	*temp;
	char	*ret;

	size = 0;
	temp = seg;
	ft_join_segs_until_sep_helper(temp, &size);
	ret = (char *)malloc(size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	temp = seg;
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->text)
		{
			size = ft_strlen(temp->text);
			ft_memcpy(ret + i, temp->text, size);
			i += size;
		}
		temp = temp->next;
	}
	return (ret[i] = '\0', ret);
}

static char	*ft_valid_filename_finder(void)
{
	int		i;
	char	*nb;
	char	*file;

	i = 0;
	nb = ft_itoa(i);
	if (!nb)
		return (NULL);
	file = ft_strjoin("./.coucou", nb);
	if (!file)
		return (free(nb), NULL);
	while (access(file, F_OK) == 0)
	{
		free(file);
		free(nb);
		i++;
		nb = ft_itoa(i);
		if (!nb)
			return (NULL);
		file = ft_strjoin("./.coucou", nb);
		if (!file)
			return (free(nb), NULL);
	}
	return (free(nb), file);
}

static int	ft_is_quoted(t_ast *n)
{
	t_seg	*temp;

	temp = n->segs;
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->type != SEG_RAW)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	ft_heredoc_rebuild(t_ast *n)
{
	t_seg	*segs;
	int		quotes;
	int		fd;
	char	*line;

	quotes = 0;
	segs = n->segs;
	if (!segs)
		return (0);
	n->limiter = ft_join_segs_until_sep(segs);
	if (!n->limiter)
		return (0);// erreur ouverture?
	n->filename = ft_valid_filename_finder();
	if (!n->filename)
		return (0);
	if (ft_is_quoted(n))
		n->limiter_quoted = TRUE;
	else
		n->limiter_quoted = FALSE;
	fd = open(n->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (0);// erreur ouverture?
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_is_limiter(line, n->limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	return (1);
}

static int	ft_redir_rebuild(t_ast *n)
{
	t_seg	*segs;
	int		quotes;

	quotes = 0;
	segs = n->segs;
	if (!segs)
		return (0);
	n->filename = ft_join_segs_until_sep(segs);
	if (!n->filename)
		return (0);
	return (1);
}

/*CMD EXPANDER*/

static char	*ft_replace_var_helper(t_seg *segs, char *s, int j, int name_len)
{
	int		s_len;
	int		after_len;
	char	*ret;
	int		i;

	s_len = ft_strlen(s);
	after_len = ft_strlen(segs->text + j + 1 + name_len);
	ret = (char *)malloc(j + s_len + after_len + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < j)
		ret[i] = segs->text[i];
	ft_memcpy(ret + i, s, s_len);
	i += s_len;
	ft_memcpy(ret + i, segs->text + j + 1 + name_len, after_len);
	i += after_len;
	ret[i] = '\0';
	return (ret);
}

static int	ft_replace_var(char *s, t_seg *segs, int name_len)
{
	int		j;
	char	*ret;

	if (!segs || !segs->text || !s || name_len < 0)
		return (0);
	j = 0;
	while (segs->text[j] && segs->text[j] != '$')
		j++;
	if (segs->text[j] != '$')
		return (1);
	ret = ft_replace_var_helper(segs, s, j, name_len);
	if (!ret)
		return (0);
	free(segs->text);
	segs->text = ret;
	return (1);
}

// static	char	*ft_find_vars(char *s, t_shell *shell)
// {
// 	int		i;
// 	t_shell	*tmp_shell;
// 	t_vars	*tmp_vars;
// 	char	*ret;

// 	i = 0;
// 	tmp_shell = shell;
// 	tmp_vars = tmp_shell->vars;
// 	while (tmp_vars)
// 	{
// 		if (ft_strncmp(s, tmp_vars->key, ft_strlen(tmp_vars->key)) == 0
// 			&& ft_strlen(s) == ft_strlen(tmp_vars->key))
// 		{
// 			ret = ft_strdup(tmp_vars->value);
// 			return (ret);
// 		}
// 		tmp_vars = tmp_vars->next;
// 	}
// 	return (ft_envp_finder(shell->envp, s));
// }

static char*	ft_exp_onevar_helper(t_seg *seg, t_shell *shell, char *found)
{
	found = ft_itoa(shell->last_status);
	if (!found)
		return (NULL);
	if (!ft_replace_var(found, seg, 1))
		return (free(found), NULL);
	free(found);
	return (ft_strchr(seg->text, '$'));
}

static char	*ft_expand_one_var_in_seg(t_seg *seg, t_shell *shell, char *s)
{
	char	*name;
	char	*found;
	int		len;

	if (*(s + 1) == '?')
		return (ft_exp_onevar_helper(seg, shell, found));
	len = ft_var_name_len(s + 1);
	if (len == 0)
		return (ft_strchr(s + 1, '$'));
	name = ft_strndup(s + 1, len);
	if (!name)
		return (NULL);
	found = ft_strdup(ft_find_vars(name, shell)->value);
	free(name);
	if (!found)
	{
		found = ft_strdup("");
		if (!found)
			return (NULL);
	}
	if (!ft_replace_var(found, seg, len))
		return (free(found), NULL);
	free(found);
	return (ft_strchr(seg->text, '$'));
}

static int	ft_expand_seg_vars(t_seg *seg, t_shell *shell)
{
	char	*s;

	if ((seg->type != SEG_RAW && seg->type != SEG_DQ) || !seg->text)
		return (1);
	s = ft_strchr(seg->text, '$');
	while (s)
	{
		s = ft_expand_one_var_in_seg(seg, shell, s);
		if (!s && ft_strchr(seg->text, '$'))
			return (0);
	}
	return (1);
}

static void	ft_var_translator(t_seg *segs, t_shell *shell)
{
	t_seg	*temp;

	temp = segs;
	while (temp)
	{
		if (!ft_expand_seg_vars(temp, shell))
			return ;
		temp = temp->next;
	}
}

static size_t	ft_word_len(t_seg **segs)
{
	t_seg	*temp;
	size_t	ret;
	int		is_quoted;

	temp = *segs;
	ret = 0;
	is_quoted = 0;
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->type == SEG_SQ || temp->type == SEG_DQ)
			is_quoted = 1;
		if (temp->text)
			ret += ft_strlen(temp->text);
		temp = temp->next;
	}
	if (ret == 0 && is_quoted)
		ret = 1;
	if (temp && temp->type == SEG_SEP)
		temp = temp->next;
	*segs = temp;
	return (ret);
}

static void	ft_append_seg_special(char *dst, t_seg *seg, size_t *i)
{
	size_t	j;

	j = 0;
	while (seg->text && seg->text[j])
	{
		if ((seg->type == SEG_SQ || seg->type == SEG_DQ) && seg->text[j] == ' ')
			dst[*i] = '\x1F';
		else
			dst[*i] = seg->text[j];
		(*i)++;
		j++;
	}
}

static t_seg	*ft_write_word(char *ret, size_t *i, t_seg *segs)
{
	t_seg	*s;
	size_t	start;
	int		is_quoted;

	s = segs;
	start = *i;
	is_quoted = 0;
	while (s && s->type != SEG_SEP)
	{
		if (s->type == SEG_SQ || s->type == SEG_DQ)
			is_quoted = 1;
		ft_append_seg_special(ret, s, i);
		s = s->next;
	}
	if (is_quoted && *i == start)
		ret[(*i)++] = '\x1E';
	if (s && s->type == SEG_SEP)
		s = s->next;
	return (s);
}

static int	ft_arg_restorer(char **arg)
{
	int		j;
	char	*s;
	char	*new;

	s = *arg;
	j = 0;
	while (s && s[j])
	{
		if (s[j] == '\x1F')
			s[j] = ' ';
		j++;
	}
	if (s && s[0] == '\x1E' && s[1] == '\0')
	{
		new = ft_strdup("");
		if (!new)
			return (0);
		free(*arg);
		*arg = new;
	}
	return (1);
}

static int	ft_restore_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (!ft_arg_restorer(&args[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_cmd_rebuild(t_ast *n)
{
	t_seg	*segs;
	t_seg	*tmp;
	char	*ret;
	size_t	size;
	size_t	i;

	segs = n->segs;
	tmp = segs;
	if (!segs)
		return (0);
	size = 0;
	while (tmp)
	{
		size += ft_word_len(&tmp);
		size++;
	}
	ret = (char *)malloc(size + 1);
	if (!ret)
		return (0);
	i = 0;
	while (segs)
	{
		segs = ft_write_word(ret, &i, segs);
		ret[i++] = ' ';
	}
	ret[i] = '\0';
	n->args = ft_split(ret, ' ');
	free(ret);
	if (!n->args)
		return (0);
	if (!ft_restore_args(n->args))
		return (ft_free_args(n->args), 0);
	return (1);
}

static int	ft_redir_expand(t_ast *n, t_shell *shell)
{
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	ft_var_translator(segs, shell);
	return (1);
}

static char	*ft_var_replace(char *line, char *found, int i, int name_len)
{
	int		found_len;
	int		after_len;
	char	*ret;

	if (!line || !found)
		return (NULL);
	found_len = ft_strlen(found);
	after_len = ft_strlen(line + i + 1 + name_len);
	ret = (char *)malloc(i + found_len + after_len + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, line, i);
	ft_memcpy(ret + i, found, found_len);
	ft_memcpy(ret + i + found_len, line + i + 1 + name_len, after_len);
	ret[i + found_len + after_len] = '\0';
	return (ret);
}

static int	ft_expand_vars_line_helper(char **line, t_shell *shell, int *i)
{
	char	*new;
	char	*found;

	found = ft_itoa(shell->last_status);
	if (!found)
		return (free(*line), 0);
	new = ft_var_replace(*line, found, *i, 1);
	(*i) += ft_strlen(found);
	free(found);
	if (!new)
		return (free(*line), 0);
	free(*line);
	*line = new;
	return (1);
}

static int	ft_expand_vars_line_helper2(char **line, t_shell *shell, int *i)
{
	int		len;
	char	*new;
	char 	*name;
	char	*found;

	len = ft_var_name_len(*line + *i + 1);
	name = ft_strndup(*line + *i + 1, len);
	if (!name)
		return (free(*line), 0);
	found = ft_strdup(ft_find_vars(name, shell)->value);
	free(name);
	if (!found)
		found = ft_strdup("");
	if (!found)
		return (free(*line), 0);
	new = ft_var_replace(*line, found, *i, len);
	(*i) += ft_strlen(found);
	free(found);
	if (!new)
		return (free(*line), 0);
	free(*line);
	*line = new;
	return (1);
}

static char	*ft_expand_vars_in_line(char *line, t_shell *shell)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			if (!ft_expand_vars_line_helper(&line, shell, &i))
				return (NULL);
		}
		else if (line[i] == '$' && ft_var_name_len(line + i + 1) != 0)
		{
			if (!ft_expand_vars_line_helper2(&line, shell, &i))
				return (NULL);
		}
		else
			i++;
	}
	return (line);
}

static int	ft_heredoc_expand(t_ast *n, t_shell *shell)
{
	int		fd_src;
	int		fd_dst;
	char	*line;
	char	*old;

	if (!n || !n->filename)
		return (0);
	if (n->limiter_quoted == TRUE)
		return (1);
	fd_src = open(n->filename, O_RDONLY);
	if (fd_src < 0)
		return (0);// erreur ouverture?
	old = n->filename;
	n->filename = ft_valid_filename_finder();
	if (!n->filename)
		return (close(fd_src), n->filename = old, 0);
	fd_dst = open(n->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_dst < 0)
		return (close(fd_src), free(n->filename), n->filename = old, 0);
	while (1)
	{
		line = get_next_line(fd_src);
		if (!line)
			break ;
		line = ft_expand_vars_in_line(line, shell);
		if (!line)
			return (close(fd_src), close(fd_dst), free(n->filename),
			n->filename = old, 0);
		write(fd_dst, line, ft_strlen(line));
		free(line);
	}
	close(fd_src);
	close(fd_dst);
	free(old);
	return (1);
}

static int	ft_cmd_expand(t_ast *n, t_shell *shell)
{
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	ft_var_translator(segs, shell);
	return (1);
}

static int	ft_rebuild_node(t_ast *n, t_shell *shell)
{
	if (n->type == NODE_CMD)
	{
		if (!ft_cmd_rebuild(n))
			return (0);	// gestion erreur
	}
	if (n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
		|| n->type == NODE_REDIR_APPEND)
	{
		if (!ft_redir_rebuild(n))
			return (0);	// gestion erreur
	}
	if (n->type == NODE_HEREDOC)
	{
		if (!ft_heredoc_expand(n, shell))
			return (0);	// gestion erreur
	}
	return (1);
}

static int	ft_expand_node(t_ast *n, t_shell *shell)
{
	if (n->type == NODE_CMD)
	{
		if (!ft_cmd_expand(n, shell))
			return (0);	// gestion erreur
	}
	if (n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
		|| n->type == NODE_REDIR_APPEND)
	{
		if (!ft_redir_expand(n, shell))
			return (0);	// gestion erreur
	}
	if (n->type == NODE_HEREDOC)
	{
		if (!ft_heredoc_rebuild(n))
			return (0);	// gestion erreur
	}
	return (1);
}

void	ft_explore_ast(t_ast **root, t_shell *shell)
{
	t_ast	*n;

	if (!root || !*root)
		return ;
	n = *root;
	if (!ft_expand_node(n, shell))
		return ;
	if (!ft_rebuild_node(n, shell))
		return ;
	if (n->left)
		ft_explore_ast(&n->left, shell);
	if (n->right)
		ft_explore_ast(&n->right, shell);
}
