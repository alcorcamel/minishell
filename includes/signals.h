#ifndef SIGNALS_H
# define SIGNALS_H

#include "base.h"

void	ft_ignore_signal(void);
void	ft_restore_signal(void);
void	ft_verif_signal(t_shell *shell, t_bool in_realine);

#endif
