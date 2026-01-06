/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:24:02 by demane            #+#    #+#             */
/*   Updated: 2026/01/06 21:52:32 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell remi.h"

int	ft_minishell(int ac, char **av)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = read_line();
		if (!line)
			return (1);// en realite erreur sans quitter
		//fonction pour ajouter a l'historique: ft_add_history(line);
		tokens = ft_lexer(line);
		free(line);
		/*
		parser
		executeur
		*/



	}

}
