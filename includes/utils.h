/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:03:11 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 15:03:11 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "base.h"
# include "parser.h"
# include "env.h"

t_bool	ft_is_directory(char *path);
void	ft_free_shell(t_shell **shell);
void	ft_perror(char *err_p);

#endif
