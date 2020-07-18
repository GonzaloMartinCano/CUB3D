/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/14/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/16/09 13:50:07 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_init_sp(t_file *f)
{
	int i;

	if (!(f->sp = (t_sprite *)malloc((sizeof(t_sprite) * f->sprite_num))))
		ft_handle_error("SPRITE.malloc error");
	if (!(f->sp_order = (int*)malloc((sizeof(int) * f->sprite_num))))
		ft_handle_error("SPRITE.malloc error");
	else
	{
		i = 0;
		while (i < f->sprite_num)
		{
			f->sp_order[i] = i;
			i++;
		}
	}
}

void			ft_calc_pos(t_file *f)
{
	int i;
	int j;
	int	k;

	i = 0;
	k = 0;
	while (i < f->ncolmax)
	{
		j = 0;
		while (j < f->nfil)
		{
			if (f->map[j][i] == 2)
			{
				f->sp[k].pos.x = j + 0.6;
				f->sp[k].pos.y = i + 0.6;
				k++;
			}
			j++;
		}
		i++;
	}
}

static void		ft_sort_sprites(t_file *f)
{
	int i;
	int j;
	int swap;

	i = 0;
	j = 0;
	swap = 0;
	while (i < f->sprite_num - 1)
	{
		j = 0;
		while (j < f->sprite_num - 1)
		{
			if (f->sp[f->sp_order[j]].distance <
				f->sp[f->sp_order[j + 1]].distance)
			{
				swap = f->sp_order[j];
				f->sp_order[j] = f->sp_order[j + 1];
				f->sp_order[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

static void		ft_calc_dist(t_file *f)
{
	int i;

	i = 0;
	while (i < f->sprite_num)
	{
		f->sp[i].distance = ((f->currentpos.x - f->sp[i].pos.x) *
			(f->currentpos.x - f->sp[i].pos.x)) +
			((f->currentpos.y - f->sp[i].pos.y) *
			(f->currentpos.y - f->sp[i].pos.y));
		i++;
	}
}

void			ft_sprite(t_file *f)
{
	ft_calc_pos(f);
	ft_calc_dist(f);
	ft_sort_sprites(f);
	ft_calc_dist_draw(f);
}
