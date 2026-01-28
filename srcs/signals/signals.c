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
	g_signal = SIGQUIT;
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

static void	ft_handle_sigint_exec(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	ft_handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	ft_ignore_signal_exec(t_shell *shell)
{
	if (shell->interactive == TRUE)
		ft_enable_echoctl();
	signal(SIGINT, ft_handle_sigint_exec);
	signal(SIGQUIT, ft_handle_sigquit);
}

// void	ft_ignore_signal_heredoc(void)
// {
// 	signal(SIGINT, ft_handle_sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

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

void	ft_restore_signal_heredoc(void)
{
	ft_disable_echoctl();
	signal(SIGINT, ft_handle_sigint_heredoc);
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

void ft_disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;  // désactiver l'affichage ^C, ^\ //
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void ft_enable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
