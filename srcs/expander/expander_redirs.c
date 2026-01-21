#include "../../includes/expander.h"

int	ft_is_quoted(t_ast *n)
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

static int	ft_heredoc_rebuild_helper(t_ast *n)
{
	t_seg	*segs;

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
	return (1);
}

int	ft_heredoc_rebuild(t_ast *n)
{
	int		fd;
	char	*line;

	if (!ft_heredoc_rebuild_helper(n))
		return (0);
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

int	ft_redir_rebuild(t_ast *n)
{
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	n->filename = ft_join_segs_until_sep(segs);
	if (!n->filename)
		return (0);
	// appeler ici le globber expand seulemtn sur in/out avec msg erreurs spe selon cas
	if (!ft_inout_globber(n))
		return (0);
	return (1);
}

int	ft_redir_expand(t_ast *n, t_shell *shell)
{
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	ft_var_translator(segs, shell);
	return (1);
}
