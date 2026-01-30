/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:03:33 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:29:47 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include "utils.h"

t_bool	ft_is_builtin(t_ast *node, t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);
int		ft_env(char **args, t_shell *shell);
int		ft_exit(char **args, t_shell *shell);
int		ft_cd(char **args, t_shell *shell);

// fonction cd_fn
int		ft_print_err_cd(void);
int		ft_print_err_cd_no_directory(char *dir);
t_bool	ft_assign_path(char **args, t_shell *shell, char **path);
t_bool	ft_check_sign(char **path, t_shell *shell);
void	ft_assign_new_pwd(t_shell *shell, char *last_path);

#endif
