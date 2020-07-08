/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_finalstring.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:45:03 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/10 11:17:25 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printflags(t_printf *x, int lenstr, char *str)
{
	if (x->flags2 == 1)
	{
		if (x->conversor != 's' && x->conversor != 'c' && x->flags == ' ')
			ft_print_precision(lenstr, x);
		ft_putchar_str(str, lenstr, x);
		ft_putchar_width(str, x->flags, lenstr, x);
		if (x->conversor != 's' && x->conversor != 'c' && x->flags == 0)
			ft_print_precision(lenstr, x);
	}
	else
	{
		ft_putchar_width(str, x->flags, lenstr, x);
		if (x->conversor != 's' && x->conversor != 'c')
			ft_print_precision(lenstr, x);
		ft_putchar_str(str, lenstr, x);
	}
}

void		ft_print_finalstring(char *str, t_printf *x)
{
	int lenstr;

	lenstr = ft_strlen(str);
	if (x->conversor == 'p')
		x->precision = lenstr;
	if ((x->precision < lenstr) && (x->conversor == 's') && x->precision >= 0)
		str = ft_cutstr(str, x);
	lenstr = ft_strlen(str);
	if (x->conversor != 's' && x->conversor != 'c' && x->precision >= x->width)
		x->width = 0;
	if (x->conversor != 's' && x->conversor != 'c' && x->precision < x->width)
	{
		if (x->precision == -1)
		{
			x->precision = 0;
			x->width = x->width - x->precision;
			x->precision = -1;
		}
		if (x->precision > -1 && x->precision >= lenstr)
		{
			x->width = x->width - x->precision;
		}
	}
	ft_printflags(x, lenstr, str);
}
