/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:15:46 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 10:27:37 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	ft_lex_error2(int i, char *s)
{
	if (i == 14)
	{
		ft_putstr_fd("minishield: error: Expected '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (i == 15)
	{
		ft_putstr_fd("minishield: error: Expected \"", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\"\n", 2);
	}
	if (i == 16)
	{
		ft_putstr_fd("minishield: error: Not handled char '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
}

void	ft_lex_err(int i, char *s)
{
	if (i == 11)
	{
		ft_putstr_fd("minishield: error: Unexpected operator '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (i == 12)
	{
		ft_putstr_fd("minishield: error: Unexistant operator '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (i == 13)
	{
		ft_putstr_fd("minishield: error: Not handled operator '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (i > 13)
		ft_lex_error2(i, s);
}
