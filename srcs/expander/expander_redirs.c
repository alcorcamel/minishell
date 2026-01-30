/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:13 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 00:17:17 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_heredoc_rebuild(t_ast *n, t_shell *shell)
{
	pid_t	pid;

	if (!ft_heredoc_rebuild_helper(n))
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		ft_heredoc_child(n, shell);
	return (ft_wait_heredoc(pid, n));
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
