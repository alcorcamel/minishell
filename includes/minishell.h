/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:23:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/28 20:48:56 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "base.h"

t_token		*ft_lexer(char *input);
int			ft_parser(t_token *tokens);
t_ast		*ft_build_and_or(t_token **cur);
int			ft_explore_ast(t_ast **root, t_shell *vars);
void		ft_ignore_signal(void);
int			ft_exec_ast(t_ast *node, t_shell *shell);
t_bool		ft_cpy_enpv(char **envp, t_shell *shell);
void		ft_print_boot(void);
char		*ft_generate_prompt(t_shell *shell);
void		ft_boot_loading(void);
void		ft_ignore_signal_exec(t_shell *shell);
void		ft_ignore_signal_prompt(void);
void		ft_verif_signal(t_shell *shell);
void		ft_free_ast(t_ast **root);
void		ft_free_shell(t_shell **shell);
void		ft_free_tokens(t_token **tok);

#endif
