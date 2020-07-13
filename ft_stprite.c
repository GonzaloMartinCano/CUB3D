/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_sprite_pos(t_file *f)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	while (y < f->nFil)
	{
		x = 0;
		while (x < f->nColMax)
		{
			if (f->map[y][x] == 2)
			{
				f->s_pos_x[i] = y + 0.6;
				f->s_pos_y[i] = x + 0.6;
				i++;
			}
			x++;
		}
		y++;
	}
}

/*int order_sprite(t_file *f)
{
	int i;
	int j;
	int swap;

	i = 0;
	j = 0;
	swap = 0;
	while (i < f->spritenum - 1) // dudo que -1 este bien	
	{
		j = 0;
		while (j < f->spritenum - 1) // dudo -1
		{
			if (f->s[f->sp_order[j]].distance < f->s[f->sp_order[j + 1]].distance)
			{
				swap = f->sp_order[j];
				f->sp_order[j] = f->sp_order[j + 1];
				f->sp_order[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}*/

int order_sprite(t_file *f)
{
	int active_index;
	int i;

	active_index = 0;
	i = 0;
	while (i < f->spritenum)
	{
		if(f->used[i] == 0)
			break ;
		++i;
	}
	active_index = i;
	i = 0;
	while (i < f->spritenum)
	{
		if(f->distance[active_index] < f->distance[i] && f->used[i] == 0)
			active_index = i;
		i++;
	}
	f->used[active_index] = 1;
	return (active_index);
}

int init_sprite(t_file *f)
{
	if (!(f->distance = (double *)malloc(sizeof(double) * f->spritenum)))
		ft_handle_error("SPRITE malloc error!");
	if (!(f->sp_order = (int *)malloc(sizeof(int) * f->spritenum)))
		ft_handle_error("SPRITE_ORDER malloc error!");
	if (!(f->used = (int *)malloc(sizeof(int) * f->spritenum)))
		ft_handle_error("SPRITE_USED malloc error!");
	if (!(f->s_pos_x = (double*)malloc(sizeof(double) * f->spritenum)))
		ft_handle_error("SPRITE_USED malloc error!");
	if (!(f->s_pos_y = (double*)malloc(sizeof(double) * f->spritenum)))
		ft_handle_error("SPRITE_USED malloc error!");
	/*else
	{
		int i;

		i = 0;
		while (i < f->spritenum)
		{
			f->sp_order[i] = i;
			i++;
		}
	}*/
}

int			ft_sprite_height(t_file *f)
{
	f->spscreenx = (int)(f->w / 2) * 1 + (f->transp.x / f->transp.y);
	f->movscreen = (int)(VMOVE / f->transp.y);
	f->spheight = abs((int)(f->h / f->transp.y)) / VDIV;
	f->drawstart_y = -f->spheight / 2 + f->h / 2 + f->movscreen;	
	f->drawstart_y = f->drawstart_y < 0 ? 0 : f->drawstart_y;
	f->drawend_y = f->spheight / 2 + f->h / 2 + f->movscreen;
	f->drawend_y = (f->drawend_y >= f->h) ? f->h - 1 : f->drawend_y;
	f->spwidth = abs((int)(f->h / f->transp.y)) / UDIV;
	f->drawstart_x = -f->spwidth / 2 + f->spscreenx;
	f->drawstart_x = (f->drawstart_x < 0 ? 0 : f->drawstart_x);
	f->drawend_x = f->spwidth / 2 + f->spscreenx;
	f->drawend_x = (f->drawend_x >= f->w ? f->w - 1 : f->drawend_x);
}

void		ft_draw_sprite_line(t_file *f, int stripe)
{
	int y;
	int d;
	int color;

	f->sptexturex = (int)(256 * (stripe - (-f->spwidth / 2 + f->spscreenx)) * TEXTURE_WIDTH / f->spwidth) / 256;
	if (f->transp.y > 0 && stripe > 0 && stripe < f->w && f->transp.y < f->z_buffer[stripe])
	{
		y = f->drawstart_y;
		while (y < f->drawend_y)
		{
			d = (y - f->movscreen) * 256 - f->h * 128 + f->spheight * 128;
			f->sptexturey = ((d * TEXTURE_HEIGHT) / f->spheight) / 256;
			color = f->tdata[4][TEXTURE_WIDTH * f->sptexturey + f->sptexturex];
			if (color != f->tdata[4][0])
				*(f->data_img + (y * f->w) + stripe) = color;
			y++;
		}
	}
}

void 		calcamera_sprite(t_file *f)
{
	int i;
	int stripe;
	int k;
	
	i = 0;
	while(i < f->spritenum)
	{
		f->distance[i] = ((f->currentpos.x - f->s_pos_x[i]) * (f->currentpos.x - f->s_pos_x[i]) + (f->currentpos.y - f->s_pos_y[i]) * (f->currentpos.y - f->s_pos_y[i]));
		i++;
	}
	i = 0;
	while (i < f->spritenum)
	{
		f->used[i] = 0;
		++i;
	}
	i = -1;
	while(++i < f->spritenum)
	{
		k = order_sprite(f);
		f->sposX = f->s_pos_x[k] - f->currentpos.x;
		f->sposY = f->s_pos_y[k] - f->currentpos.y;
		f->inv_det = 1.0 / (f->m.plane.x * f->m.dir.y - f->m.dir.x * f->m.plane.y);
		f->transp.x = f->inv_det * (f->m.dir.y * f->sposX - f->m.dir.x * f->sposY);
		f->transp.y = f->inv_det * (-f->m.plane.y * f->sposX + f->m.plane.x * f->sposY);
		ft_sprite_height(f);
		stripe = f->drawstart_x - 1;
		while (++stripe < f->drawend_x)
			ft_draw_sprite_line(f, stripe);
		i++;
	}
}

void ft_draw_sprite(t_file *f)
{
	calcamera_sprite(f);
}