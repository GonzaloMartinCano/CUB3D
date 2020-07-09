/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 13:50:16 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		ft_canmove(int x)
{
	if (x == 1 || x == 2)
		return (0);
	return (1);
}

int		ft_key_press(int key, t_file *f)
{
	if (key == KEY_ESC)
		mlx_destroy_window(f->mlx, f->win);
	if (key == KEY_W)
		f->m.W = 1;
	if (key == KEY_S)
		f->m.S = 1;
	if (key == KEY_A)
		f->m.A = 1;
	if (key == KEY_D)
		f->m.D = 1;
	if (key == KEY_LEFT)
		f->m.L = 1;
	if (key == KEY_RIGHT)
		f->m.R = 1;
	return (0);
}

int		ft_key_release(int key, t_file *f)
{
	if (key == KEY_ESC)
		mlx_destroy_window(f->mlx, f->win);
	if (key == KEY_W)
		f->m.W = 0;
	if (key == KEY_S)
		f->m.S = 0;
	if (key == KEY_A)
		f->m.A = 0;
	if (key == KEY_D)
		f->m.D = 0;
	if (key == KEY_LEFT)
		f->m.L = 0;
	if (key == KEY_RIGHT)
		f->m.R = 0;
	return (0);
}
