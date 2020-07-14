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
		if (f->m.sideDist.x < f->m.sideDist.y)
		{
			f->m.sideDist.x += f->m.deltaDist.x;
			f->m.mapX += f->m.stepX;
			f->m.side = 0;
		}
		else
		{
			f->m.sideDist.y += f->m.deltaDist.y;
			f->m.mapY += f->m.stepY;
			f->m.side = 1;
		}
		if (f->map[f->m.mapX][f->m.mapY] == 1)
			hit = 1;
	}
}

void		ft_wall_height(t_file *f)
{
	if (f->m.side == 0)
		f->m.perpWallDist = (f->m.mapX - f->currentpos.x
			+ (1 - f->m.stepX) / 2) / f->m.rayDir.x;
	else
		f->m.perpWallDist = (f->m.mapY - f->currentpos.y
			+ (1 - f->m.stepY) / 2) / f->m.rayDir.y;
	f->m.lineHeight = (int)(f->h / f->m.perpWallDist);
	f->m.drawStart = (-f->m.lineHeight / 2) + f->h / 2;
	if (f->m.drawStart < 0)
		f->m.drawStart = 0;
	f->m.drawEnd = (f->m.lineHeight / 2) + f->h / 2;
	if (f->m.drawEnd >= f->h || f->m.drawEnd == 0)
		f->m.drawEnd = f->h - 1;
}
