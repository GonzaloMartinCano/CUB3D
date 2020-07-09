/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_calcdir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_calcdirns(t_file *f)
{
	if (f->dir == 'N')
	{
		f->m.dir.x = -1.0;
		f->m.dir.y = 0.0;
		f->m.plane.x = 0.0;
		f->m.plane.y = 0.66;
	}
	else if (f->dir == 'S')
	{
		f->m.dir.x = 1.0;
		f->m.dir.y = 0.0;
		f->m.plane.x = 0.0;
		f->m.plane.y = -0.66;
	}
}

int			ft_calcdirew(t_file *f)
{
	if (f->dir == 'E')
	{
		f->m.dir.x = 0.0;
		f->m.dir.y = 1.0;
		f->m.plane.x = 0.66;
		f->m.plane.y = 0.00;
	}
	else if (f->dir == 'W')
	{
		f->m.dir.x = 0.0;
		f->m.dir.y = -1.0;
		f->m.plane.x = -0.66;
		f->m.plane.y = 0.00;
	}
}
