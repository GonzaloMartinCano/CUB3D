/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 13:50:07 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_calcamera(t_file *f, int x)
{
	f->m.mapX = (int)f->currentpos.x;
	f->m.mapY = (int)f->currentpos.y;
	f->m.cameraX = (2 * x / (double)f->w) - 1;
	f->m.rayDir.x = f->m.dir.x + f->m.plane.x * f->m.cameraX;
	f->m.rayDir.y = f->m.dir.y + f->m.plane.y * f->m.cameraX;
	f->m.deltaDist.x = fabs(1 / f->m.rayDir.x);
	f->m.deltaDist.y = fabs(1 / f->m.rayDir.y);
}

static int		ft_calcstep(t_file *f)
{
	if (f->m.rayDir.x < 0)
	{
		f->m.stepX = -1;
		f->m.sideDist.x = (f->currentpos.x - f->m.mapX) * f->m.deltaDist.x;
	}
	else
	{
		f->m.stepX = 1;
		f->m.sideDist.x = (f->m.mapX + 1.0 - f->currentpos.x)
			* f->m.deltaDist.x;
	}
	if (f->m.rayDir.y < 0)
	{
		f->m.stepY = -1;
		f->m.sideDist.y = (f->currentpos.y - f->m.mapY) * f->m.deltaDist.y;
	}
	else
	{
		f->m.stepY = 1;
		f->m.sideDist.y = (f->m.mapY + 1.0 - f->currentpos.y)
			* f->m.deltaDist.y;
	}
}

static void		ft_draw_line(t_file *f, int x)
{
	int i;
	int color;

	i = 0;
	while (i < f->m.drawStart)
	{
		*(f->data_img + (i * f->w) + x) = 7719150;
		i++;
	}
	while (i <= f->m.drawEnd)
	{
		f->m.textY = (int)f->m.textpos & (TEXTURE_HEIGHT - 1);
		f->m.textpos += f->m.textstep;
		color = f->tdata[f->m.textside][TEXTURE_HEIGHT * f->m.textY
			+ f->m.textX];
		*(f->data_img + (i * f->w) + x) = color;
		i++;
	}
	while (i <= f->h)
	{
		*(f->data_img + (i * f->w) + x) = 7364912;
		i++;
	}
}

int				ft_draw(t_file *f)
{
	int hit;
	int x;

	x = 0;
	while (x < f->w)
	{
		ft_calcamera(f, x);
		ft_calcstep(f);
		ft_hit_wall(f);
		ft_wall_height(f);
		ft_color_side(f);
		ft_config_texture(f);
		ft_draw_line(f, x);
		f->z_buffer[x] = f->m.perpWallDist;
		x++;
	}
}
