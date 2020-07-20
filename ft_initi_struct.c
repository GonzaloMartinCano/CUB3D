/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_init_file_struct(t_file *f)
{
	int i;

	i = 0;
	f->w = 0;
	f->h = 0;
	f->rtn = 0;
	f->sprite = 0;
	while (i < 4)
		f->texture[i++] = 0;
	i = 0;
	while (i < 3)
		f->cc[i++] = -1;
	while (i >= 0)
		f->cf[i--] = -1;
	f->c_c = ft_strdup("");
	f->c_f = ft_strdup("");
	f->buff = ft_strdup("");
	f->nfil = 0;
	f->ncolmax = 0;
	f->dir = '\0';
	i = 0;
	while (i < 8)
		f->countmap[i++] = 0;
	f->mapreaded = 1;
}

void		ft_init_file_struct2(t_file *f)
{
	f->pos[0] = 0;
	f->pos[1] = 0;
	f->m.stepx = 0;
	f->m.stepy = 0;
	f->m.sidedist.x = 0;
	f->m.sidedist.y = 0;
	f->m.dir.x = 0.0;
	f->m.dir.y = 0.0;
	f->m.rotspeed = 0.03;
	f->m.movespeed = 0.05;
	f->m.side = 0;
	f->m.w = 0;
	f->m.s = 0;
	f->m.a = 0;
	f->m.d = 0;
	f->m.l = 0;
	f->m.r = 0;
	f->m.textside = 0;
	f->m.texty = 0;
	f->m.textx = 0;
	f->m.textstep = 0;
	f->sprite_num = 0;
}
