/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:15:46 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 01:41:41 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_lex_err(int i, char *s)
{
	if (i == 11)
		ft_printf_fd(STDERR_FILENO, "Error: Unexpected operator '%s'\n", s);
	if (i == 12)
		ft_printf_fd(STDERR_FILENO, "Error: Unexistant operator '%s'\n", s);
	if (i == 13)
		ft_printf_fd(STDERR_FILENO, "Error: Not handled operator '%s'\n", s);
	if (i == 14)
		ft_printf_fd(STDERR_FILENO, "Error: Expected '%s'\n", s);
	if (i == 15)
		ft_printf_fd(STDERR_FILENO, "Error: Expected \"%s\"\n", s);
	if (i == 16)
		ft_printf_fd(STDERR_FILENO, "Error: Not handled char '%s'\n", s);
}
