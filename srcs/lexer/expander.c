
#include "lexer.h"

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

static int	ft_words_filler(char **args, t_ast *n, int words)
{
	int		i;
	t_seg	*temp;

	i = -1;
	temp = n->segs;
	while (++i < words)
	{
		n->args[i] = ft_join_segs_until_sep(temp);
		if (!n->args[i])
			return (ft_free_args(n->args), 0);
		while (temp && temp->type != SEG_SEP)
			temp = temp->next;
		if (temp->type == SEG_SEP && temp->next)
			temp = temp->next;
	}
	return (1);
}

static int	ft_words_counter(t_ast *n)
{
	t_seg	*segs;
	int		ret;

	ret = 0;
	segs = n->segs;
	if (!segs)
		return (0);
	while (segs)
	{
		if (segs->type == SEG_SEP)
			ret++;
		segs = segs->next;
	}
	return (ret);
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
	file = ft_strjoin("./coucou", nb);
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

static int	ft_heredoc_expander(t_ast *n)
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
		return (0);
	n->filename = ft_valid_filename_finder();
	if (!n->filename)
		return (0);
	fd = open(n->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
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

static int	ft_redir_expander(t_ast *n)
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

static int ft_var_translator(t_seg *segs)
{
	t_seg	*temp;
	char	c;

	c = '$';
	temp = segs;
	while (temp && temp->type != SEG_SEP)
	{
		if (temp->type == SEG_RAW && temp->text)
		{
			// if (ft_strchr(temp->text, (int)c))
		}
		temp = temp->next;
	}
	return (1);
}

static int	ft_cmd_expander(t_ast *n)
{
	t_seg	*segs;
	int		quotes;
	int		words;

	words = 0;
	quotes = 0;
	segs = n->segs;
	if (!segs)
		return (0);
	words = ft_words_counter(n);
	n->args = calloc(words + 1, sizeof(char *));
	if (!n->args)
		return (ft_free_args(n->args), 0);
	n->args[words] = NULL;
	if (!ft_words_filler(n->args, n, words))
		return (ft_free_args(n->args), 0);
	return (1);
}

static int	ft_expand_node(t_ast *n)
{
	if (n->type == NODE_CMD)
	{
		if (!ft_cmd_expander(n))
			return (0);	// gestion erreur
	}
	if (n->type == NODE_REDIR_IN || n->type == NODE_REDIR_OUT
		|| n->type == NODE_REDIR_APPEND)
	{
		if (!ft_redir_expander(n))
			return (0);	// gestion erreur
	}
	if (n->type == NODE_HEREDOC)
	{
		if (!ft_heredoc_expander(n))
			return (0);	// gestion erreur
	}
	return (1);
}

void	ft_explore_ast(t_ast **root)
{
	t_ast	*n;

	if (!root || !*root)
		return ;
	n = *root;
	if (!ft_expand_node(n))
		return ;
	if (n->left)
		ft_explore_ast(&n->left);
	if (n->right)
		ft_explore_ast(&n->right);
}

