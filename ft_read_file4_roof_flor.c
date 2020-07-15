/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file4_roof_flor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	localisdigit(t_file *f, char **test)
{
	int		i;
	int		j;
	char	**aux;

	i = 0;
	j = 0;
	aux = test;
	while (i <= 2)
	{
		j = 0;
		while (aux[i][j])
		{
			if ((!ft_isdigit(aux[i][j]) && aux[i][j] != ' ')
				|| (ft_isdigit(aux[i][j - 1]) && aux[i][j] == ' '))
				return (f->rtn = -1);
			j++;
		}
		i++;
	}
	return (f->rtn);
}

static char	localstrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
		{
			i++;
		}
		s++;
	}
	return (i);
}

int			ft_handle_cfloor(t_file *f)
{
	char **test;
	char **test2;

	if (*f->line == 'F' && *f->line)
	{
		test2 = ft_split(++f->line, ',');
		if (localisdigit(f, test2) == -1)
			ft_handle_error("ERROR en color suelo");
		if ((f->cf[0] = ft_atoi(test2[0])) >= 0)
			if (f->cf[0] > 255 || f->cf[0] < 0)
				return ((f->rtn = -1));
		if ((f->cf[1] = ft_atoi(test2[1])) >= 0)
			if (f->cf[1] > 255 || f->cf[1] < 0)
				return ((f->rtn = -1));
		if ((f->cf[2] = ft_atoi(test2[2])) >= 0)
			if (f->cf[2] > 255 || f->cf[2] < 0)
				return ((f->rtn = -1));
	}
	return (f->rtn);
}

int			ft_handle_croof(t_file *f)
{
	char **test;
	char **test2;

	if (*f->line == 'C' && *f->line)
	{
		test2 = ft_split(++f->line, ',');
		if (localisdigit(f, test2) == -1)
			ft_handle_error("ERROR en color cielo");
		if ((f->cc[0] = ft_atoi(test2[0])) >= 0)
			if (f->cc[0] > 255 || f->cc[0] < 0)
				return ((f->rtn = -1));
		if ((f->cc[1] = ft_atoi(test2[1])) >= 0)
			if (f->cc[1] > 255 || f->cc[1] < 0)
				return ((f->rtn = -1));
		if ((f->cc[2] = ft_atoi(test2[2])) >= 0)
			if (f->cc[2] > 255 || f->cc[2] < 0)
				return ((f->rtn = -1));
	}
	return (f->rtn);
}
