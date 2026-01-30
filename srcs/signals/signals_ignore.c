/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_ignore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:50:00 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 22:52:10 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

void	ft_ignore_signal_exec(void)
{
	signal(SIGINT, ft_handle_sigint_exec);
	signal(SIGQUIT, ft_handle_sigquit);
}

void	ft_ignore_signal_prompt(void)
{
	signal(SIGINT, ft_handle_sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
