/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:15:46 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:16:16 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_lex_err(int i, char *s)
{
	if (i == 11)
		printf("Error: Unexpected operator '%s'\n", s);
	if (i == 12)
		printf("Error: Unexistant operator '%s'\n", s);
	if (i == 13)
		printf("Error: Not handled operator '%s'\n", s);
	if (i == 14)
		printf("Error: Expected '%s'\n", s);
	if (i == 15)
		printf("Error: Expected \"%s\"\n", s);
	if (i == 16)
		printf("Error: Not handled char '%s'\n", s);
}
