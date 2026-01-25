#ifndef SIGNALS_H
# define SIGNALS_H

#include "base.h"

void	ft_ignore_signal_exec(void);
void	ft_ignore_signal_prompt(void);
void	ft_restore_signal(void);
void	ft_verif_signal(t_shell *shell);
void	ft_restore_signal_heredoc(void);
// void	ft_ignore_signal_heredoc(void);
void	ft_disable_echoctl(void);
void	ft_ignore_signal(void);
void	ft_enable_echoctl(void);

#endif
