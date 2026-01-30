/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:37 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 10:27:44 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_pars_err(int i, char *s)
{
	if (i == 1)
	{
		ft_putstr_fd("minishield: syntax error near unexpected token '", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (i == 2)
		ft_putstr_fd("minishield: syntax error near unexpected token newline\n", 2);
}
