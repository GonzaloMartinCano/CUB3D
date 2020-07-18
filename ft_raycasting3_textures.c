/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting3_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_color_side(t_file *f)
{
	double dx;
	double dy;

	dx = f->m.mapx - f->currentpos.x;
	dy = f->m.mapy - f->currentpos.y;
	if (dx < 0 && f->m.side == 0)
		f->m.textside = 3;
	if (dx > 0 && f->m.side == 0)
		f->m.textside = 2;
	if (dy < 0 && f->m.side == 1)
		f->m.textside = 1;
	if (dy > 0 && f->m.side == 1)
		f->m.textside = 0;
}

void		ft_color(t_file *f)
{
	if (f->map[f->m.mapx][f->m.mapy] == 1)
		ft_color_side(f);
	if (f->map[f->m.mapx][f->m.mapy] == 2)
		f->m.color = 16712447;
}

void		ft_config_texture(t_file *f)
{
	if (f->m.side == 0)
		f->m.wallx = f->currentpos.y + f->m.perpwalldist * f->m.raydir.y;
	else
		f->m.wallx = f->currentpos.x + f->m.perpwalldist * f->m.raydir.x;
	f->m.wallx -= floor(f->m.wallx);
	f->m.textx = (int)(f->m.wallx * (double)TEXTURE_WIDTH);
	if (f->m.side == 0 && f->m.raydir.x > 0)
		f->m.textx = TEXTURE_WIDTH - f->m.textx - 1;
	if (f->m.side == 1 && f->m.raydir.y < 0)
		f->m.textx = TEXTURE_WIDTH - f->m.textx - 1;
	f->m.textstep = 1.0 * TEXTURE_HEIGHT / f->m.lineheight;
	f->m.textpos = (f->m.drawstart - f->h / 2 + f->m.lineheight / 2)
		* f->m.textstep;
}
