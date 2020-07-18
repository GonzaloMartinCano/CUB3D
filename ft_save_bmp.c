/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/14/08 20:05:20 by gmartin-          #+#    #+#             */
/*   Updated: 2020/16/09 13:50:07 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define DPI 2835
#define BMP_HEADER_SIZE 54

void			checkcorrectargument(t_file *f, char *aux)
{
	int		len;
	char	*aux2;

	len = ft_strlen(aux);
	aux2 = ft_substr(aux, len - 4, 4);
	if (len < 5)
		ft_handle_error("ERROR: IN FILE NAME\n");
	if (ft_strcmp(".cub", aux2) != 4)
		ft_handle_error("ERROR: IN FILE NAME\n");
	if ((f->fd = open(aux, O_RDONLY)) <= 0)
		ft_handle_error("ERROR: WHEN OPEN FILE\n");
	free(aux2);
}

void			ft_init_bmp(t_file *f, t_bmp *bmp)
{
	int		ppm;

	ppm = 40 * DPI;
	bmp->type[0] = 'B';
	bmp->type[1] = 'M';
	bmp->file_size = (4 + 54) * f->w * f->h;
	bmp->reserved = 0;
	bmp->offset = 14;
	bmp->size_header = 40;
	bmp->width = f->w;
	bmp->height = f->h;
	bmp->planes = 1;
	bmp->bit_count = 32;
	bmp->compression = 0;
	bmp->image_size = bmp->file_size;
	bmp->ppm_x = ppm;
	bmp->ppm_y = ppm;
	bmp->clr_used = 0;
	bmp->clr_important = 0;
}

static void		write_bmp(int fd, t_bmp *bmp)
{
	write(fd, &bmp->type, sizeof(bmp->type));
	write(fd, &bmp->file_size, sizeof(bmp->file_size));
	write(fd, &bmp->reserved, sizeof(bmp->reserved));
	write(fd, &bmp->offset, sizeof(bmp->offset));
	write(fd, &bmp->size_header, sizeof(bmp->size_header));
	write(fd, &bmp->width, sizeof(bmp->width));
	write(fd, &bmp->height, sizeof(bmp->height));
	write(fd, &bmp->planes, sizeof(bmp->planes));
	write(fd, &bmp->bit_count, sizeof(bmp->bit_count));
	write(fd, &bmp->compression, sizeof(bmp->compression));
	write(fd, &bmp->file_size, sizeof(bmp->file_size));
	write(fd, &bmp->ppm_x, sizeof(bmp->ppm_x));
	write(fd, &bmp->ppm_y, sizeof(bmp->ppm_y));
	write(fd, &bmp->clr_used, sizeof(bmp->clr_used));
	write(fd, &bmp->clr_important, sizeof(bmp->clr_important));
}

void			ft_save_bmp(t_file *f)
{
	int		fd;
	int		x;
	int		y;
	int		color;
	t_bmp	bmp;

	if ((fd = open("cub3D.bmp", O_WRONLY | O_CREAT, S_IRWXU |
	O_TRUNC | O_APPEND)) < 0)
		ft_handle_error("ERROR BMP Failed. Not created");
	ft_init_bmp(f, &bmp);
	write_bmp(fd, &bmp);
	y = 0;
	while (y < f->h)
	{
		x = 0;
		while (x < f->w)
		{
			color = *(f->data_img + (f->h - y - 1) *
			f->w + x);
			write(fd, &color, 4);
			x++;
		}
		y++;
	}
	close(fd);
}
