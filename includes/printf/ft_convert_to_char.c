/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 20:26:11 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/06 18:10:28 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_options(t_printf *x)
{
	if (*x->format == '-' || *x->format == '0')
		ft_flags(x);
	if (*x->format == '*' || ft_isdigit(*x->format))
		ft_width(x);
	if (*x->format == '.')
		ft_precision(x);
	if (*x->format != '\0')
		ft_convert_to_char(x);
	if (*x->format == '%')
	{
		ft_print_finalstring("%", x);
		return ;
	}
}

void	ft_convert_to_char(t_printf *x)
{
	if (*x->format == 's')
		ft_printf_str(x);
	if (*x->format == 'c')
		ft_print_char(x);
	if (*x->format == 'd')
		ft_print_int(x);
	if (*x->format == 'i')
		ft_print_int(x);
	if (*x->format == 'u')
		ft_print_unsignedint(x);
	if (*x->format == 'x')
		ft_print_x(x);
	if (*x->format == 'X')
		ft_print_altx(x);
	if (*x->format == 'p')
		ft_print_p(x);
}
