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
		return (0);
	n->filename = ft_valid_filename_finder();
	if (!n->filename)
		return (free(n->limiter), n->limiter = NULL,
			free(n->filename), n->filename = NULL, 0);
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
	pid_t	pid;
	int		status;
	int		nb_lines;

	if (!ft_heredoc_rebuild_helper(n))
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		ft_restore_signal_heredoc();
		fd = open(n->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			free(n->limiter);
			n->limiter = NULL;
			free(n->filename);
			n->filename = NULL;
			exit(1);
		}
		nb_lines = 0;
		while (1)
		{
			nb_lines++;
			write(1, "> ", 2);
			line = get_next_line(0);
			if (!line)
			{
				ft_printf("\nminishell: warning: here-document at line ");
				ft_printf("%d delimited by end-of-file (wanted `%s')\n",
					nb_lines, n->limiter);
				break ;
			}
			if (ft_is_limiter(line, n->limiter))
			{
				free(line);
				break ;
			}
			write(fd, line, ft_strlen(line));
			free(line);
		}
		close(fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (1);
		else
		{
			unlink(n->filename);
			return (0);
		}
	}
	if (WIFSIGNALED(status))
	{
		unlink(n->filename);
		return (0);
	}
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
	if (!ft_inout_globber(n))
		return (free(n->filename), n->filename = NULL, 0);
	return (1);
}

int	ft_redir_expand(t_ast *n, t_shell *shell)
{
	t_seg	*segs;

	segs = n->segs;
	if (!segs)
		return (0);
	if (!ft_var_translator(n, segs, shell))
		return (0);
	return (1);
}
