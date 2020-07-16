/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 13:50:16 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_handle_error(char *str)
{
	ft_printf("%s", str);
	exit(0);
}

int				ft_handle_rgb(t_file *f)
{
	f->ccieling = (((f->cc[0] * 256) * 256) + (f->cc[1] * 256) + f->cc[2]);
	f->cfloor = (((f->cf[1] * 256) * 256) + (f->cf[1] * 256) + f->cf[2]);
	if (f->ccieling < 0 || f->cfloor < 0)
		ft_handle_error("ERROR color");
}

int				ft_read_src_file2(t_file *f)
{
	if (f->cf[0] == -1 || f->cf[1] == -1 || f->cf[2] == -1)
	{
		if ((ft_handle_cfloor(f)) == -1)
			ft_handle_error("ERROR WHILE READING TEXTURES\n");
	}
	else if (f->cc[0] == -1 || f->cc[1] == -1 || f->cc[2] == -1)
	{
		if ((ft_handle_croof(f)) == -1)
			ft_handle_error("ERROR WHILE READING TEXTURES\n");
	}
	else if (f->mapreaded == -1)
	{
		if ((ft_handle_map_read(f) == -1))
			ft_handle_error("ERROR WHILE READING MAP");
	}
	return (f->rtn);
}

int				ft_read_src_file(t_file *f)
{
	if (!f->w && !f->h)
	{
		if ((ft_handle_resolution(f)) == -1 || f->w < 200 ||
			f->w > 1920 || f->h < 200 || f->h > 1080)
			ft_handle_error("ERROR WHILE READING RESOLUTION\n");
	}
	else if (!f->texture[0] || !f->texture[1] || !f->texture[2]
		|| !f->texture[3])
	{
		if ((ft_handle_textures(f)) == -1)
			ft_handle_error("TERROR WHILE READING TEXTURES\n");
	}
	else if (f->sprite == 0)
	{
		if ((ft_handle_spritex(f)) == -1)
			ft_handle_error("ERROR WHILE READING TEXTURES\n");
	}
	ft_read_src_file2(f);
	return (f->rtn);
}
