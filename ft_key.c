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

int		ft_canmove(int x)
{
	if (x == 1 || x == 2)
		return (0);
	return (1);
}

int		ft_exitgame(t_file *f)
{
	int i;

	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(f->mlx, f->textures[i]);
		f->textures[i] = NULL;
		i++;
	}
	free(f->buff);
	free(f->z_buffer);
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->win);
	exit(EXIT_SUCCESS);
}

int		ft_key_press(int key, t_file *f)
{
	if (key == KEY_ESC)
		ft_exitgame(f);
	if (key == KEY_W)
		f->m.w = 1;
	if (key == KEY_S)
		f->m.s = 1;
	if (key == KEY_A)
		f->m.a = 1;
	if (key == KEY_D)
		f->m.d = 1;
	if (key == KEY_LEFT)
		f->m.l = 1;
	if (key == KEY_RIGHT)
		f->m.r = 1;
	return (0);
}

int		ft_key_release(int key, t_file *f)
{
	if (key == KEY_ESC)
		ft_exitgame(f);
	if (key == KEY_W)
		f->m.w = 0;
	if (key == KEY_S)
		f->m.s = 0;
	if (key == KEY_A)
		f->m.a = 0;
	if (key == KEY_D)
		f->m.d = 0;
	if (key == KEY_LEFT)
		f->m.l = 0;
	if (key == KEY_RIGHT)
		f->m.r = 0;
	return (0);
}
