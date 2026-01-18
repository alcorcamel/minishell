#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

t_bool	ft_is_builtin(t_ast *node, t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_exit(char **args);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);
int		ft_env(char **args, t_shell *shell);
int		ft_exit(char **args);
int		ft_cd(char **arg);

#endif
