/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:23:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/17 00:14:25 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "base.h"

t_token		*ft_lexer(char *input);
int			ft_parser(t_token *tokens);
t_ast		*ft_build_and_or(t_token **cur);
void		ft_explore_ast(t_ast **root, t_shell *vars);
int			ft_exec_root(t_ast *node, t_shell *shell);

#endif
