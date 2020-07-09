/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:56:00 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/06 17:49:14 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(t_printf *x)
{
	if (*x->format == '-')
	{
		x->flags = ' ';
		x->flags2 = 1;
		x->format++;
	}
	else if (*x->format == '0')
	{
		x->flags = '0';
		x->flags2 = -1;
		x->format++;
	}
}

void	ft_width(t_printf *x)
{
	if (*x->format == '*')
	{
		x->width = va_arg(x->ap, int);
		if (x->width < 0)
		{
			x->width *= -1;
			x->flags2 = 1;
			x->flags = ' ';
		}
		x->format++;
	}
	else
	{
		x->width = ft_atoi(x->format);
		while (ft_isdigit(*x->format))
			x->format++;
	}
}
