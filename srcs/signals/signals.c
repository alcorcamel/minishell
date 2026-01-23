#include "../../includes/signals.h"

volatile sig_atomic_t	g_signal = 0;

static void	ft_handle_sigint(int sig)
{
	g_signal = sig;
}

void	ft_ignore_signal(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_verif_signal(t_shell *shell, t_bool in_realine)
{
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		if (in_realine == FALSE)
		{
			rl_replace_line("", 0);
			rl_redisplay();
		}
		shell->last_status = 130;
		g_signal = 0;
	}
}
