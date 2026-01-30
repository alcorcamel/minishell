/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:19:10 by demane            #+#    #+#             */
/*   Updated: 2026/01/29 23:36:45 by demane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int			i;
	int			counter_write;
	va_list		ap;
	t_format	format;

	i = 0;
	counter_write = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			format = ft_readformat(&str[++i]);
			format.fd = STDOUT_FILENO;
			ft_printarg(format, ap, &counter_write);
			i += format.length;
		}
		else
		{
			ft_putchar_fd(str[i++], 1);
			counter_write++;
		}
	}
	va_end(ap);
	return (counter_write);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int			i;
	int			counter_write;
	va_list		ap;
	t_format	format;

	i = 0;
	counter_write = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			format = ft_readformat(&str[++i]);
			format.fd = fd;
			ft_printarg(format, ap, &counter_write);
			i += format.length;
		}
		else
		{
			ft_putchar_fd(str[i++], format.fd);
			counter_write++;
		}
	}
	va_end(ap);
	return (counter_write);
}
