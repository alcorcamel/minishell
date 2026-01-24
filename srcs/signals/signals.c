#include "../../includes/signals.h"

volatile sig_atomic_t	g_signal = 0;

static void	ft_handle_sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_handle_sigquit(int sig)
{
	g_signal = SIGQUIT;
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

static void	ft_handle_sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

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
