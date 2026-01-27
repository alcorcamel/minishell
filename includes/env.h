#ifndef ENV_H
# define ENV_H

#include "base.h"

t_bool	ft_cpy_enpv(char **envp, t_shell *shell);
t_vars	*ft_find_vars(char *key, t_shell *shell);
t_vars	*ft_create_new_vars(char *var_envp, t_bool is_exported);
void	ft_add_vars(t_shell *shell, t_vars *vars);
char	*ft_get_key_from_var_envp(char *var_envp);
t_bool	ft_get_value_from_var_envp(char *var_envp, char **value);
void	ft_free_vars(t_vars **var);
t_bool	ft_del_vars(t_vars *del, t_shell *shell);
char	**ft_make_envp(t_vars *vars);
void	ft_free_all_env(t_vars **head);

#endif
