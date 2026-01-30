/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:37 by demane            #+#    #+#             */
/*   Updated: 2026/01/30 01:42:20 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	ft_pars_err(int i, char *s)
{
	if (i == 1)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected \
token '%s'\n", s);
	else if (i == 2)
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected \
token newline\n");
}
