/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:58:19 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/03 12:18:12 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_precision(t_printf *x)
{
	x->format++;
	if (*x->format <= '9' && *x->format >= '0')
		x->precision = ft_atoi(x->format);
	else
		x->precision = 0;
	if (x->precision < 0)
		x->precision = -1;
	if (*x->format == '*')
	{
		x->precision = va_arg(x->ap, int);
		x->format++;
	}
	while (ft_isdigit(*x->format))
		x->format++;
}
