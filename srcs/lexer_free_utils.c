/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:43:38 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/07 21:03:47 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_remi.h"

void	ft_free_segs(t_seg *seg)
{
	t_seg	*next;

	while (seg)
	{
		next = seg->next;
		free(seg->text);
		free(seg);
		seg = next;
	}
}

void	ft_free_tokens(t_token *tok)
{
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		free(tok->value);
		ft_free_segs(tok->segs);
		free(tok);
		tok = next;
	}
}
