/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:16:39 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:16:40 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_seg	*ft_segnew(t_segtype type, char *text)
{
	t_seg	*ret;

	ret = (t_seg *)ft_calloc(1, sizeof(t_seg));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->text = text;
	ret->next = NULL;
	return (ret);
}

static void	ft_segadd_back(t_seg **lst, t_seg *newseg)
{
	t_seg	*tmp;

	if (!lst || !newseg)
		return ;
	if (!*lst)
	{
		*lst = newseg;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newseg;
}

int	ft_add_seg(t_seg **segs, t_segtype type, char *start, int len)
{
	char	*s;
	t_seg	*node;

	s = ft_strndup(start, len);
	if (!s)
		return (0);
	node = ft_segnew(type, s);
	if (!node)
		return (free(s), 0);
	ft_segadd_back(segs, node);
	return (1);
}

static void	ft_join_segs_helper(t_seg *temp, size_t *size)
{
	while (temp)
	{
		if (temp->type != SEG_SEP && temp->text)
			*size += ft_strlen(temp->text);
		temp = temp->next;
	}
}

char	*ft_join_segs(t_seg *seg)
{
	size_t	size;
	size_t	i;
	t_seg	*temp;
	char	*ret;

	size = 0;
	temp = seg;
	ft_join_segs_helper(temp, &size);
	ret = (char *)malloc(size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	temp = seg;
	while (temp)
	{
		if (temp->type != SEG_SEP && temp->text)
		{
			size = ft_strlen(temp->text);
			ft_memcpy(ret + i, temp->text, size);
			i += size;
		}
		temp = temp->next;
	}
	return (ret[i] = '\0', ret);
}
