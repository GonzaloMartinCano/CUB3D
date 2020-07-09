/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:01:21 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/03 19:14:15 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_str(t_printf *x)
{
	char	*ptr;

	ptr = va_arg(x->ap, char*);
	if (ptr == NULL)
		ptr = "(null)";
	x->conversor = 's';
	ft_print_finalstring(ptr, x);
}

void	ft_print_char(t_printf *x)
{
	char c[2];

	c[0] = (char)va_arg(x->ap, int);
	c[1] = '\0';
	if (c[0] == '\0')
	{
		x->len++;
		x->width--;
		x->conversor = 'c';
	}
	ft_print_finalstring(c, x);
}
