
#include "../../includes/executor.h"
#include "../../includes/expander.h"

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
	char	*name;
	char	*found;

	len = ft_var_name_len(*line + *i + 1);
	name = ft_strndup(*line + *i + 1, len);
	if (!name)
		return (free(*line), 0);
	if (ft_find_vars(name, shell))
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


static int	ft_heredoc_exp_helper(t_shell *shell, int fd_src, int fd_dst)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd_src);
		if (!line)
			break ;
		line = ft_expand_vars_in_line(line, shell);
		if (!line)
			return (0);
		write(fd_dst, line, ft_strlen(line));
		free(line);
	}
	close(fd_src);
	close(fd_dst);
	return (1);
}

int	ft_heredoc_expand(t_ast *n, t_shell *shell)
{
	int		fd_src;
	int		fd_dst;
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
	if (!ft_heredoc_exp_helper(shell, fd_src, fd_dst))
		return (close(fd_src), close(fd_dst), free(n->filename),
			n->filename = old, 0);
	free(old);
	return (1);
}
