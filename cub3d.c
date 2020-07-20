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

int			ft_isspace(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\f' || s[i] == '\r' ||
			s[i] == '\t' || s[i] == '\v')
			i++;
		break ;
	}
	return (i);
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
		if (ft_read_src_file(f) == -1)
			ft_handle_error("ERROR WHILE READ CONFIG");
		if (br == 0)
			break ;
		free(line);
	}
	free(line);
	ft_handle_rgb(f);
	if (alloc_map(f) != -1)
		if (map_check(f->pos[0], f->pos[1], f) == -1)
			ft_handle_error("ERROR: WHILE CHEC MAP000\n");
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
