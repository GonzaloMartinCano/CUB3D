/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file5_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_handle_map_read(t_file *f)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_isdigit(f->line[0]) || f->line[0] == ' ')
	{
		i = ft_strlen(f->line);
		if (f->buff == NULL)
			temp = ft_strdup(f->line);
		else
			temp = ft_strjoin(f->buff, f->line);
		free(f->buff);
		f->buff = temp;
		temp = ft_strjoin(f->buff, "\n");
		free(f->buff);
		f->buff = temp;
		if (f->ncolmax == 0 || f->ncolmax < i)
			f->ncolmax = i;
		f->nfil++;
	}
	return (f->rtn);
}

void		ft_filling_matrix(t_file *f, int k, int i, int j)
{
	if (f->buff[k] == '0' || f->buff[k] == '1' || f->buff[k] == '2')
	{
		f->map[i][j] = (int)f->buff[k] - '0';
		if (f->buff[k] == '2')
			f->sprite_num++;
	}
	else if (f->buff[k] == ' ')
		f->map[i][j] = 4;
	else if (f->buff[k] == 'N' || f->buff[k] == 'S'
		|| f->buff[k] == 'E' || f->buff[k] == 'W')
	{
		if (f->dir == '\0')
		{
			f->map[i][j] = 0;
			f->dir = f->buff[k];
			ft_calcdirns(f);
			ft_calcdirew(f);
			f->pos[0] = i;
			f->currentpos.x = i + 0.5;
			f->pos[1] = j;
			f->currentpos.y = j + 0.5;
		}
	}
	else
		ft_handle_error("YUJU");
}

int			alloc_map(t_file *f)
{
	int i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!(f->map = ft_calloc(f->nfil, sizeof(int *))))
		return (0);
	else
	{
		while (i[0] < f->nfil && f->buff[i[2]])
		{
			if (!(f->map[i[0]] = ft_calloc(f->ncolmax, sizeof(int *))))
				return (0);
			i[1] = 0;
			while (i[1] < f->ncolmax && f->buff[i[2]] != '\n')
			{
				ft_filling_matrix(f, i[2], i[0], i[1]);
				i[2]++;
				i[1]++;
			}
			i[2]++;
			i[0]++;
		}
	}
	return (0);
}
