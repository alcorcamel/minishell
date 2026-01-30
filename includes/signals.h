/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:06:02 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:31:02 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "base.h"

void	ft_ignore_signal_exec(void);
void	ft_ignore_signal_prompt(void);
void	ft_restore_signal(void);
void	ft_verif_signal(t_shell *shell);
void	ft_restore_signal_heredoc(void);
void	ft_ignore_signal(void);
void	ft_handle_sigint_prompt(int sig);
void	ft_handle_sigquit(int sig);
void	ft_handle_sigint_exec(int sig);
void	ft_handle_sigint_heredoc(int sig);

#endif
