/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:12:15 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/10 11:26:38 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_putchar(char *finals, char c)
{
	char base[2];

	base[0] = c;
	base[1] = '\0';
	finals = ft_strjoin(finals, base);
	return (finals);
}

char	*ft_putnbrbase(unsigned long int nb, char c, char *finals, t_printf *x)
{
	unsigned long int n;

	n = nb;
	if (n >= 16)
	{
		finals = ft_putnbrbase(n / 16, c, finals, x);
	}
	if ((n % 16) < 10)
		finals = ft_putchar(finals, (n % 16) + '0');
	if ((n % 16) > 9)
		finals = ft_putchar(finals, (n % 16) + c);
	return (finals);
}

void	ft_print_x(t_printf *x)
{
	unsigned int	nb;
	char			*finals;

	finals = malloc(sizeof(char) * 1);
	finals[0] = '\0';
	nb = va_arg(x->ap, unsigned int);
	finals = ft_putnbrbase(nb, 'W', finals, x);
	if (x->precision > -1)
		x->flags = ' ';
	ft_print_finalstring(finals, x);
}

void	ft_print_altx(t_printf *x)
{
	unsigned int	nb;
	char			*finals;

	finals = malloc(sizeof(char) * 1);
	finals[0] = '\0';
	nb = va_arg(x->ap, unsigned int);
	finals = ft_putnbrbase(nb, '7', finals, x);
	if (x->precision > -1)
		x->flags = ' ';
	ft_print_finalstring(finals, x);
}

void	ft_print_p(t_printf *x)
{
	unsigned long int	nb;
	char				*finals;
	char				*p;

	p = "0x";
	x->conversor = 'p';
	finals = malloc(sizeof(char) * 1);
	finals[0] = '\0';
	nb = va_arg(x->ap, unsigned long int);
	if (nb == 0 && x->precision > -1)
	{
		finals = "0x";
		ft_print_finalstring(finals, x);
		return ;
	}
	finals = ft_putnbrbase(nb, 'W', finals, x);
	finals = ft_strjoin(p, finals);
	ft_print_finalstring(finals, x);
}
