/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:54:55 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/06 18:08:12 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

typedef struct	s_printf
{
	int		len;
	int		width; 
	int		precision;
	char	flags;
	int		flags2;
	char	conversor;
	char	*format;
	char	*finalstring;
	int		negative;
	va_list	ap;

}				t_printf;

void	ft_options(t_printf *x);
void	ft_convert_to_char(t_printf *x);
void	ft_precision(t_printf *x);
void	ft_printf_str(t_printf *x);
void	ft_print_char(t_printf *x);
void	ft_print_int(t_printf *x);
void	ft_print_unsignedint(t_printf *x);
void	ft_print_x(t_printf *x);
void	ft_print_altx(t_printf *x);
void	ft_print_p(t_printf *x);
void	ft_print_finalstring(char *str, t_printf *x);
void	ft_flags(t_printf *x);
void	ft_width(t_printf *x);
void	ft_putchar_str(char *str,int lenstr, t_printf *x);
void	ft_putchar_width(char *str, char c, int lenstr, t_printf *x);
void	ft_print_precision(int lenstr, t_printf *x);
char	*ft_cutstr(char *str, t_printf *x);
int		ft_printf(const char *format, ...);

#endif
