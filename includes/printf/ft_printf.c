/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:18:26 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/10 11:47:23 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"

void	ft_clean(t_printf *x)
{
	x->flags = ' ';
	x->conversor = 'a';
	x->width = 0;
	x->flags2 = -1;
	x->precision = -1;
	x->negative = 0;
}

int		ft_printf(const char *format, ...)
{
	t_printf	x;

	va_start(x.ap, format);
	x.format = (char*)format;
	x.len = 0;
	ft_clean(&x);
	while (*x.format != '\0')
	{
		ft_clean(&x);
		if (*x.format == '%')
		{
			x.format++;
			ft_options(&x);
			x.format++;
		}
		else
		{
			write(1, x.format, 1);
			x.format++;
			x.len++;
		}
	}
	va_end(x.ap);
	return (x.len);
}
