/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:19:57 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:19:58 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

volatile sig_atomic_t	g_signal = 0;

static void	ft_handle_sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_handle_sigquit(int sig)
{
	(void)sig;
	g_signal = SIGQUIT;
}

static void	ft_handle_sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

static void	ft_handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	ft_ignore_signal_exec()
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

void ft_restore_signal_heredoc(void)
{
	t_sigaction	sa;

	sa.sa_handler = ft_handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_verif_signal(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_status = 130;
		g_signal = 0;
	}
	if (g_signal == SIGQUIT)
	{
		shell->last_status = 131;
		g_signal = 0;
	}
}
