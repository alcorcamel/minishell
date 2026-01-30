/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:15:59 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:24:41 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(t_format f, void *p)
{
	int				hex_len;
	int				space_count;
	int				printed;
	unsigned long	address;

	address = (unsigned long)p;
	if (address)
		hex_len = 2 + ft_hexlen(address);
	else
		hex_len = 5;
	space_count = ft_getspacecount(f, hex_len, 0, 0);
	printed = 0;
	if (!f.flag_minus)
		printed += ft_putnchar(' ', space_count, f.fd);
	if (address)
	{
		printed += ft_putnstr("0x", 2, f.fd);
		printed += ft_printnbrhex(f, address, f.fd);
	}
	else
		printed += ft_putnstr("(nil)", 5, f.fd);
	if (f.flag_minus)
		printed += ft_putnchar(' ', space_count, f.fd);
	return (printed);
}
