#ifndef BUILTINS_H
# define BUILTINS_H

# include "base.h"

t_bool	ft_is_builtin(char *cmd);
int		ft_echo(char **arg);
int		ft_pwd(char **arg);
int		ft_exit(char **arg);
int		ft_export(char **arg, t_shell *shell);
int		ft_unset(char **arg);
int		ft_env(char **arg);
int		ft_exit(char **arg);
int		ft_cd(char **arg);

#endif
