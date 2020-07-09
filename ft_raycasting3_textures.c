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

static void		ft_color_side(t_file *f)
{
	double dx;
	double dy;

	dx = f->m.mapX - f->currentpos.x;
	dy = f->m.mapY - f->currentpos.y;
	if (dx < 0 && f->m.side == 0)
		f->m.textside = 3;
	if (dx > 0 && f->m.side == 0)
		f->m.textside = 2;
	if (dy < 0 && f->m.side == 1)
		f->m.textside = 1;
	if (dy > 0 && f->m.side == 1)
		f->m.textside = 0;
}

void			ft_color(t_file *f)
{
	if (f->map[f->m.mapX][f->m.mapY] == 1)
		ft_color_side(f);
	if (f->map[f->m.mapX][f->m.mapY] == 2)
		f->m.color = 16712447;
}

void			ft_config_texture(t_file *f)
{
	if (f->m.side == 0)
		f->m.wallX = f->currentpos.y + f->m.perpWallDist * f->m.rayDir.y;
	else
		f->m.wallX = f->currentpos.x + f->m.perpWallDist * f->m.rayDir.x;
	f->m.wallX -= floor(f->m.wallX);
	f->m.textX = (int)(f->m.wallX * (double)TEXTURE_WIDTH);
	if (f->m.side == 0 && f->m.rayDir.x > 0)
		f->m.textX = TEXTURE_WIDTH - f->m.textX - 1;
	if (f->m.side == 1 && f->m.rayDir.y < 0)
		f->m.textX = TEXTURE_WIDTH - f->m.textX - 1;
	f->m.textstep = 1.0 * TEXTURE_HEIGHT / f->m.lineHeight;
	f->m.textpos = (f->m.drawStart - f->h / 2 + f->m.lineHeight / 2)
		* f->m.textstep;
}
