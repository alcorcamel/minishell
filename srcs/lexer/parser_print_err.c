/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:16:56 by rbourdon          #+#    #+#             */
/*   Updated: 2026/01/12 21:19:26 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_pars_err(int i, char *s)
{
	if (i == 1)
		printf("minishell: syntax error near unexpected token '%s'\n", s);
	else if (i == 2)
		printf("minishell: syntax error near unexpected token newline\n");

}
