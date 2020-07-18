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
	f->m.mapx = (int)f->currentpos.x;
	f->m.mapy = (int)f->currentpos.y;
	f->m.camerax = (2 * x / (double)f->w) - 1;
	f->m.raydir.x = f->m.dir.x + f->m.plane.x * f->m.camerax;
	f->m.raydir.y = f->m.dir.y + f->m.plane.y * f->m.camerax;
	f->m.deltadist.x = fabs(1 / f->m.raydir.x);
	f->m.deltadist.y = fabs(1 / f->m.raydir.y);
}

static int		ft_calcstep(t_file *f)
{
	if (f->m.raydir.x < 0)
	{
		f->m.stepx = -1;
		f->m.sidedist.x = (f->currentpos.x - f->m.mapx) * f->m.deltadist.x;
	}
	else
	{
		f->m.stepx = 1;
		f->m.sidedist.x = (f->m.mapx + 1.0 - f->currentpos.x)
			* f->m.deltadist.x;
	}
	if (f->m.raydir.y < 0)
	{
		f->m.stepy = -1;
		f->m.sidedist.y = (f->currentpos.y - f->m.mapy) * f->m.deltadist.y;
	}
	else
	{
		f->m.stepy = 1;
		f->m.sidedist.y = (f->m.mapy + 1.0 - f->currentpos.y)
			* f->m.deltadist.y;
	}
}

static void		ft_draw_line(t_file *f, int x)
{
	int i;
	int color;

	i = 0;
	while (i < f->m.drawstart)
	{
		*(f->data_img + (i * f->w) + x) = f->ccieling;
		i++;
	}
	while (i <= f->m.drawend)
	{
		f->m.texty = (int)f->m.textpos & (TEXTURE_HEIGHT - 1);
		f->m.textpos += f->m.textstep;
		color = f->tdata[f->m.textside][TEXTURE_HEIGHT * f->m.texty
			+ f->m.textx];
		*(f->data_img + (i * f->w) + x) = color;
		i++;
	}
	while (i <= f->h)
	{
		*(f->data_img + (i * f->w) + x) = f->cfloor;
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
		f->z_buffer[x] = f->m.perpwalldist;
		x++;
	}
}
