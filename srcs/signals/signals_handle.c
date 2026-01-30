/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:48:51 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 22:50:50 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

void	ft_handle_sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_handle_sigquit(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
}

void	ft_handle_sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	ft_handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}
