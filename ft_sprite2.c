/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/14/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/16/09 13:50:07 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_calc_sprite_camera(int i, t_file *f)
{
	f->sp[f->sp_order[i]].cam_pos.x =
		f->sp[f->sp_order[i]].pos.x - f->currentpos.x;
	f->sp[f->sp_order[i]].cam_pos.y =
		f->sp[f->sp_order[i]].pos.y - f->currentpos.y;
	f->inv_det = 1 / (f->m.plane.x * f->m.dir.y - f->m.dir.x * f->m.plane.y);
	f->transform.x = f->inv_det * (f->m.dir.y * f->sp[f->sp_order[i]].cam_pos.x
		- f->m.dir.x * f->sp[f->sp_order[i]].cam_pos.y);
	f->transform.y = f->inv_det * (-f->m.plane.y
		* f->sp[f->sp_order[i]].cam_pos.x + f->m.plane.x
		* f->sp[f->sp_order[i]].cam_pos.y);
	f->sp_screen_x = (int)((f->w / 2) * (1 + f->transform.x / f->transform.y));
	f->sp_height = abs((int)(f->h / f->transform.y));
}

void		ft_draw_sprite_line(t_file *f, int y, int d)
{
	int stripe;
	int color;

	stripe = f->start_sp_x;
	while (stripe < f->end_sp_x)
	{
		f->tex_x = (int)(256 * (stripe - (-f->sp_width / 2 + f->sp_screen_x))
		* TEXTURE_WIDTH / f->sp_width) / 256;
		if (f->transform.y > 0 && stripe > 0 && stripe < f->w
			&& f->transform.y < f->z_buffer[stripe])
		{
			y = f->start_sp_y;
			while (y < f->end_sp_y)
			{
				d = (y - f->movescreen) * 256 - f->h * 128 + f->sp_height * 128;
				f->tex_y = ((d * TEXTURE_HEIGHT) / f->sp_height) / 256;
				if (f->tex_y >= 0)
					color = f->tdata[4][TEXTURE_WIDTH * f->tex_y + f->tex_x];
				if (color != f->tdata[4][0])
					*(f->data_img + (y * f->w) + stripe) = color;
				y++;
			}
		}
		stripe++;
	}
}

void		ft_calc_dist_draw(t_file *f)
{
	int i;
	int y;
	int d;

	i = 0;
	while (i < f->sprite_num)
	{
		ft_calc_sprite_camera(i, f);
		f->movescreen = (int)(VMOVE / f->transform.y);
		f->start_sp_y = -f->sp_height / 2 + f->h / 2 + f->movescreen;
		if (f->start_sp_y < 0)
			f->start_sp_y = 0;
		f->end_sp_y = f->sp_height / 2 + f->h / 2 + f->movescreen;
		if (f->end_sp_y >= f->h)
			f->end_sp_y = f->h - 1;
		f->sp_width = abs((int)(f->h / f->transform.y));
		f->start_sp_x = -f->sp_width / 2 + f->sp_screen_x;
		if (f->start_sp_x < 0)
			f->start_sp_x = 0;
		f->end_sp_x = f->sp_width / 2 + f->sp_screen_x;
		if (f->end_sp_x >= f->w)
			f->end_sp_x = f->w - 1;
		ft_draw_sprite_line(f, y, d);
		i++;
	}
}
