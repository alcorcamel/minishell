/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_rebuild.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:17:36 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 01:02:40 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/executor.h"

static void	ft_append_seg_special(char *dst, t_seg *seg, size_t *i)
{
	size_t	j;

	j = 0;
	while (seg->text && seg->text[j])
	{
		if ((seg->type == SEG_SQ || seg->type == SEG_DQ) && seg->text[j] == ' ')
			dst[*i] = '\x1F';
		else if ((seg->type != SEG_SQ && seg->type != SEG_DQ)
			&& seg->text[j] == '*')
			dst[*i] = '\x1D';
		else
			dst[*i] = seg->text[j];
		(*i)++;
		j++;
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

static int	ft_cmd_rebuild_helper(t_seg *segs, size_t *size, char **ret)
{
	t_seg	*tmp;

	tmp = segs;
	*size = 0;
	while (tmp)
	{
		(*size) += ft_word_len(&tmp);
		(*size)++;
	}
	*ret = (char *)malloc((*size) + 1);
	if (!*ret)
		return (0);
	return (1);
}

int	ft_cmd_rebuild(t_ast *n)
{
	t_seg	*segs;
	char	*ret;
	size_t	size;
	size_t	i;

	segs = n->segs;
	if (!ft_cmd_rebuild_helper(segs, &size, &ret))
		return (0);
	i = 0;
	while (segs)
	{
		segs = ft_write_word(ret, &i, segs);
		ret[i++] = ' ';
	}
	ret[i] = '\0';
	if (ft_is_empty(ret))
		return (ft_set_empty_cmd(n, ret));
	return (ft_cmd_rebuild2(n, &ret));
}
