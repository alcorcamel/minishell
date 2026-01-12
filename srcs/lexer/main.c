/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:24:02 by demane            #+#    #+#             */
/*   Updated: 2026/01/12 15:23:24 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*ft_type_printer(t_token_type t)
{
	if (t == TOKEN_WORD)
		return ("WORD");
	if (t == TOKEN_PIPE)
		return ("PIPE");
	if (t == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	if (t == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	if (t == TOKEN_APPEND)
		return ("APPEND");
	if (t == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (t == TOKEN_LBRACKET)
		return ("LBRACKET");
	if (t == TOKEN_RBRACKET)
		return ("RBRACKET");
	return (NULL);
}

static void	ft_print_segs(t_seg *s)
{
	while (s)
	{
		if (s->type == SEG_RAW)
			printf(" RAW:%s", s->text);
		else if (s->type == SEG_SQ)
			printf(" SQ:%s", s->text);
		else if (s->type == SEG_DQ)
			printf(" DQ:%s", s->text);
		s = s->next;
	}
}

static void	ft_printer(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("noeud:%d %s", i, ft_type_printer(lst->type));
		if (lst->value)
			printf(" value=%s", lst->value);
		if (lst->segs)
			ft_print_segs(lst->segs);
		printf("\n");
		lst = lst->next;
		i++;
	}
}

//clear; cc ./srcs/main.c ./srcs/lexer/*.c ./srcs/lexer/lexer.h -lreadline -lhistory -lncurses
// clear; cc ./srcs/lexer/* -lreadline -lhistory -lncurses

int	main(int ac, char **av)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("JARVIS$ ");
		if (!line)
			return (1);// en realite erreur sans quitter
		tokens = ft_lexer(line);
		ft_printer(tokens);
		add_history (line);
		//ft_parser(tokens);
		free(line);
		// if (ft_paser(tokens) == 1)
		// 	exec!
	}
	return (0);
}
