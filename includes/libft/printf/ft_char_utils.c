/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:07:24 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:10:55 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchar(char c, int n, int fd)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd(c, fd);
	return (n);
}

int	ft_printchar(t_format f, char c)
{
	int		len_char;
	int		space_count;
	int		printed;

	len_char = 1;
	space_count = ft_getspacecount(f, len_char, 0, 0);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count, f.fd);
	printed += ft_putnchar(c, 1, f.fd);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count, f.fd);
	return (printed);
}
