/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
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
	f->mapreaded = -1;
	f->buff = ft_strdup("");
	f->nfil = 0;
	f->ncolmax = 0;
	f->dir = '\0';
}

void		ft_init_file_struct2(t_file *f)
{
	f->pos[0] = 1;
	f->pos[1] = 1;
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

int			ft_read(t_file *f)
{
	int		br;
	char	*line;

	ft_init_file_struct(f);
	ft_init_file_struct2(f);
	while ((br = get_next_line(f->fd, &line)) >= 0)
	{
		f->line = line;
		if (!(ft_strchr("NWESRFC102 ", f->line[0])))
			ft_handle_error("ERROR: NOT INIT PLAYER\n");
		if (ft_read_src_file(f) == -1)
			return (-1);
		free(line);
		if (br == 0)
			break ;
	}
	ft_handle_rgb(f);
	alloc_map(f);
	if (f->dir == '\0')
		ft_handle_error("ERROR: NOT INIT PLAYER\n");
	if (f->rtn == -1)
		ft_handle_error("ERROR: WHILE ALLOC MAP\n");
	if ((f->rtn = map_check(f->pos[0], f->pos[1], f)) == -1)
		ft_handle_error("ERROR: WHILE CHECK MAP\n");
	close(f->fd);
	return (f->rtn);
}

void		ft_chek_args(t_file *f, int argc, char *argv[])
{
	char	*aux;
	int		len;

	f->bmp_active = 0;
	if (argc < 2 || argc > 3)
		ft_handle_error("ERROR NEED ONLY 2 ARGUMENTS \n");
	if (argc == 2)
	{
		aux = argv[1];
		checkcorrectargument(f, aux);
	}
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0))
			ft_handle_error("ERROR: NEED A VALID ARGUMENTS");
		else
		{
			aux = argv[1];
			checkcorrectargument(f, aux);
			f->bmp_active = 1;
		}
	}
}

int			main(int argc, char *argv[])
{
	t_file f;

	ft_chek_args(&f, argc, argv);
	if (!(f.mlx = mlx_init()))
		ft_handle_error("ERROR: WHILE OPEN MLX\n");
	ft_read(&f);
	if (!(f.win = mlx_new_window(f.mlx, f.w, f.h, "CUB3D by Gonzalo Martin")))
		ft_handle_error("ERROR: WHILE OPEN MLX\n");
	f.img = mlx_new_image(f.mlx, f.w, f.h);
	f.data_img = (int *)mlx_get_data_addr(f.img, &f.bits_per_pixel,
		&f.size_line, &f.endian);
	ft_init_sp(&f);
	ft_draw(&f);
	ft_sprite(&f);
	if (f.bmp_active == 1)
	{
		ft_save_bmp(&f);
		ft_exitgame(&f);
	}
	mlx_hook(f.win, 2, 1, ft_key_press, &f);
	mlx_hook(f.win, 3, 2, ft_key_release, &f);
	mlx_loop_hook(f.mlx, ft_move_draw, &f);
	mlx_hook(f.win, 17, 1L << 17, ft_exitgame, &f);
	mlx_loop(f.mlx);
	return (0);
}
