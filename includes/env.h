#ifndef ENV_H
# define ENV_H

#include "base.h"

int		ft_print_envp(t_shell *shell);
t_bool	ft_cpy_enpv(char **envp, t_shell *shell);

#endif