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
	f->nFil = 0;
	f->nColMax = 0;
	f->dir = '\0';
}

void		ft_init_file_struct2(t_file *f)
{
	f->pos[0] = 1;
	f->pos[1] = 1;
	f->m.stepX = 0;
	f->m.stepY = 0;
	f->m.sideDist.x = 0;
	f->m.sideDist.y = 0;
	f->m.dir.x = 0.0;
	f->m.dir.y = 0.0;
	f->m.rotSpeed = 0.03;
	f->m.moveSpeed = 0.05;
	f->m.side = 0;
	f->m.W = 0;
	f->m.S = 0;
	f->m.A = 0;
	f->m.D = 0;
	f->m.L = 0;
	f->m.R = 0;
	f->m.textside = 0;
	f->m.textY = 0;
	f->m.textX = 0;
	f->m.textstep = 0;
	f->sprite_num = 0;
}

int			ft_read(t_file *f)
{
	int br;

	ft_init_file_struct(f);
	ft_init_file_struct2(f);
	while ((br = get_next_line(f->fd, &f->line)) >= 0)
	{
		if (ft_read_src_file(f) == -1)
			return (-1);
		if (br == 0)
			break ;
	}
	ft_handle_rgb(f);
	alloc_map(f);
	if (f->dir == '\0')
		ft_handle_error("ERROR no init player dir!\n");
	if (f->rtn == -1)
		ft_handle_error("MAP.ERROR while allock. asshole\n");
	if ((f->rtn = map_check(f->pos[0], f->pos[1], f)) == -1)
		ft_handle_error("MAP.ERROR while check. stupid\n");
	return (f->rtn);
}

void		ft_chek_args(t_file *f, int argc, char *argv[])
{
	char	*aux;
	int		len;

	if (argc == 2)
	{
		aux = argv[1];
		len = ft_strlen(argv[1]);
		if (len < 5)
			ft_handle_error("ERROR file name\n");
		if (ft_strcmp(".cub", ft_substr(argv[1], len - 4, 4)) != 4)
			ft_handle_error("ERROR file name \n");
		if ((f->fd = open(argv[1], O_RDONLY)) <= 0)
			ft_handle_error("ERROR open file\n");
	}
	else
		ft_handle_error("ERROR NEED ONLY 2 ARGUMENTS \n");
}

int			main(int argc, char *argv[])
{
	t_file f;

	ft_chek_args(&f, argc, argv);
	if (!(f.mlx = mlx_init()))
		ft_handle_error("MAP.ERROR while open_mlx stupid\n");
	ft_read(&f);
	if (!(f.win = mlx_new_window(f.mlx, f.w, f.h, "CUB3D by Gonzalo Martin")))
		ft_handle_error("MAP.ERROR while open_mlx_window\n");
	f.img = mlx_new_image(f.mlx, f.w, f.h);
	f.data_img = (int *)mlx_get_data_addr(f.img, &f.bits_per_pixel,
		&f.size_line, &f.endian);
	ft_init_sp(&f);
	ft_draw(&f);
	mlx_hook(f.win, 2, 1, ft_key_press, &f);
	mlx_hook(f.win, 3, 2, ft_key_release, &f);
	mlx_loop_hook(f.mlx, ft_move_draw, &f);
	mlx_hook(f.win, 17, 1L<<17, ft_exitgame, &f);
	mlx_loop(f.mlx);
	return (0);
}
