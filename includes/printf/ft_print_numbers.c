/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 11:17:30 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/10 11:26:24 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_print_int(t_printf *x)
{
	char	*integer;
	int		i;

	i = (va_arg(x->ap, int));
	if (i < 0 && (x->flags == '0' || x->precision > 0) && i != -2147483648)
	{
		x->negative = 1;
		x->len++;
		i = i * -1;
		x->width -= 1;
	}
	if (i == -2147483648)
		integer = ft_strdup("-2147483648");
	else
		integer = ft_itoa(i);
	if (x->precision > -1)
		x->flags = ' ';
	ft_print_finalstring(integer, x);
}

static char			*ft_unsigneditoa(unsigned int n)
{
	unsigned int		aux;
	int					len;
	char				*str;

	aux = n;
	len = 1;
	while (aux /= 10)
		len++;
	if ((str = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

void				ft_print_unsignedint(t_printf *x)
{
	char			*integer;
	unsigned int	z;

	z = va_arg(x->ap, unsigned int);
	integer = ft_unsigneditoa(z);
	if (x->precision > -1)
		x->flags = ' ';
	ft_print_finalstring(integer, x);
}
