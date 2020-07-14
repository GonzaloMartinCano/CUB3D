/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 13:50:16 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		ft_movementud(t_file *f)
{
	if (f->m.W > 0)
	{
		if (ft_canmove(f->map[(int)(f->currentpos.x + f->m.dir.x
			* f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x += f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)f->currentpos.x][(int)
			(f->currentpos.y + f->m.dir.y * f->m.moveSpeed)]))
			f->currentpos.y += f->m.dir.y * f->m.moveSpeed;
	}
	if (f->m.S > 0)
	{
		if (ft_canmove(f->map[(int)(f->currentpos.x - f->m.dir.x
			* f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x -= f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)f->currentpos.x][(int)
			(f->currentpos.y - f->m.dir.y * f->m.moveSpeed)]))
			f->currentpos.y -= f->m.dir.y * f->m.moveSpeed;
	}
	return (0);
}

int		ft_movementlr(t_file *f)
{
	if (f->m.A > 0)
	{
		if (ft_canmove(f->map[(int)(f->currentpos.x)]
			[(int)(f->currentpos.y + f->m.dir.x * f->m.moveSpeed)]))
			f->currentpos.y += f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)(f->currentpos.x - f->m.dir.y
			* f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x -= f->m.dir.y * f->m.moveSpeed;
	}
	if (f->m.D > 0)
	{
		if (ft_canmove(f->map[(int)(f->currentpos.x)]
			[(int)(f->currentpos.y - f->m.dir.x * f->m.moveSpeed)]))
			f->currentpos.y -= f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)(f->currentpos.x + f->m.dir.y
			* f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x += f->m.dir.y * f->m.moveSpeed;
	}
	return (0);
}

int		ft_rotationleft(t_file *f)
{
	t_vector auxdir;
	t_vector auxplane;

	if (f->m.L > 0)
	{
		auxplane.x = f->m.plane.x;
		auxdir.x = f->m.dir.x;
		f->m.dir.x = f->m.dir.x * cos(f->m.rotSpeed)
			- f->m.dir.y * sin(f->m.rotSpeed);
		f->m.dir.y = auxdir.x * sin(f->m.rotSpeed)
			+ f->m.dir.y * cos(f->m.rotSpeed);
		auxplane.x = f->m.plane.x;
		f->m.plane.x = f->m.plane.x * cos(f->m.rotSpeed)
			- f->m.plane.y * sin(f->m.rotSpeed);
		f->m.plane.y = auxplane.x * sin(f->m.rotSpeed)
			+ f->m.plane.y * cos(f->m.rotSpeed);
	}
}

int		ft_rotationright(t_file *f)
{
	t_vector auxdir;
	t_vector auxplane;

	if (f->m.R > 0)
	{
		auxplane.x = f->m.plane.x;
		auxdir.x = f->m.dir.x;
		f->m.dir.x = f->m.dir.x * cos(-f->m.rotSpeed)
			- f->m.dir.y * sin(-f->m.rotSpeed);
		f->m.dir.y = auxdir.x * sin(-f->m.rotSpeed)
			+ f->m.dir.y * cos(-f->m.rotSpeed);
		auxplane.x = f->m.plane.x;
		f->m.plane.x = f->m.plane.x * cos(-f->m.rotSpeed)
			- f->m.plane.y * sin(-f->m.rotSpeed);
		f->m.plane.y = auxplane.x * sin(-f->m.rotSpeed)
			+ f->m.plane.y * cos(-f->m.rotSpeed);
	}
	return (0);
}

int		ft_move_draw(t_file *f)
{
	ft_movementud(f);
	ft_movementlr(f);
	ft_rotationleft(f);
	ft_rotationright(f);
	mlx_destroy_image(f->mlx, f->img);
	f->img = mlx_new_image(f->mlx, f->w, f->h);
	f->data_img = (int *)mlx_get_data_addr(f->img, &f->bits_per_pixel,
		&f->size_line, &f->endian);
	ft_draw(f);
	ft_sprite(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}
