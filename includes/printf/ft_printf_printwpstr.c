/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printwpstr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:53:45 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/10 11:29:03 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_str(char *str, int lenstr, t_printf *x)
{
	if (*str == '0' && x->precision == 0)
		return ;
	if (x->conversor == 'c')
	{
		write(1, "\0", 1);
		return ;
	}
	if ((x->precision < lenstr) && (x->conversor == 's') && x->precision >= 0)
		str = ft_cutstr(str, x);
	while (*str)
	{
		write(1, str, 1);
		str++;
		x->len++;
	}
}

void	ft_putchar_width(char *str, char c, int lenstr, t_printf *x)
{
	if ((x->conversor != 's' && x->precision >= x->width) ||
		(*str == '0' && x->precision == 0))
		lenstr = 0;
	if (x->negative > 0 && x->flags == '0')
	{
		write(1, "-", 1);
		x->negative = 0;
	}
	if (x->precision < lenstr)
		x->width = x->width - lenstr;
	if (x->conversor == 's' && x->precision >= lenstr)
		x->width = x->width - lenstr;
	while (x->width > 0)
	{
		write(1, &c, 1);
		x->width--;
		x->len++;
	}
	if (x->negative > 0 && x->flags2 == 1)
	{
		write(1, "-", 1);
		x->negative = 0;
	}
}

void	ft_print_precision(int lenstr, t_printf *x)
{
	if (x->negative > 0)
	{
		write(1, "-", 1);
		x->negative = 0;
	}
	while (x->precision > lenstr)
	{
		write(1, "0", 1);
		x->len++;
		lenstr++;
	}
}

char	*ft_cutstr(char *str, t_printf *x)
{
	char *aux;

	aux = ft_substr(str, 0, x->precision);
	return (aux);
}
