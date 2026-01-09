/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 09:17:17 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/09 10:05:08 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_lex_err(int i, char *s)
{
	if (i == 11)
		printf("Error: Unexcepted operator '%s'\n", s);
	if (i == 12)
		printf("Error: Unexistant operator '%s'\n", s);
	if (i == 13)
		printf("Error: Not handled operator '%s'\n", s);
}
