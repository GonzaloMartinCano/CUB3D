/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting2_wall.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_hit_wall(t_file *f)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (f->m.sidedist.x < f->m.sidedist.y)
		{
			f->m.sidedist.x += f->m.deltadist.x;
			f->m.mapx += f->m.stepx;
			f->m.side = 0;
		}
		else
		{
			f->m.sidedist.y += f->m.deltadist.y;
			f->m.mapy += f->m.stepy;
			f->m.side = 1;
		}
		if (f->map[f->m.mapx][f->m.mapy] == 1)
			hit = 1;
	}
}

void		ft_wall_height(t_file *f)
{
	if (f->m.side == 0)
		f->m.perpwalldist = (f->m.mapx - f->currentpos.x
			+ (1 - f->m.stepx) / 2) / f->m.raydir.x;
	else
		f->m.perpwalldist = (f->m.mapy - f->currentpos.y
			+ (1 - f->m.stepy) / 2) / f->m.raydir.y;
	f->m.lineheight = (int)(f->h / f->m.perpwalldist);
	f->m.drawstart = (-f->m.lineheight / 2) + f->h / 2;
	if (f->m.drawstart < 0)
		f->m.drawstart = 0;
	f->m.drawend = (f->m.lineheight / 2) + f->h / 2;
	if (f->m.drawend >= f->h || f->m.drawend == 0)
		f->m.drawend = f->h - 1;
}
