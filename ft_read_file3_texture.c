/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file3_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/09 12:10:58 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			*first_compro(t_file *f, char *aux)
{
	if ((f->line = ft_strchr(f->line, '.')))
	{
		if (*(f->line + 1) == '/')
			aux = f->line;
		else
			ft_handle_error("ERROR: PATH TEXTURE INVALID\n");
	}
	else
		ft_handle_error("ERROR: PATH TEXTURE INVALID\n");
	return (aux);
}

int				ft_handle_path_texture(t_file *f, int i)
{
	char	*aux;
	char	*ext;
	int		w;
	int		h;

	aux = first_compro(f, aux);
	aux++;
	if (ft_check_extension((ext = ft_strchr(aux, '.'))) < 0)
		ft_handle_error("ERROR: PATH TEXTURE INVALID\n");
	if ((f->texture[i] = open(--aux, O_RDONLY)) < 0)
		ft_handle_error("ERROR: PATH TEXTURE INVALID\n");
	else
	{
		f->countmap[i + 1]++;
		f->textures[i] = mlx_xpm_file_to_image(f->mlx, aux, &w, &h);
		f->tdata[i] = (int *)mlx_get_data_addr(f->textures[i],
			&f->bits_per_pixel, &f->size_line, &f->endian);
		close(f->texture[i]);
	}
	return (f->rtn);
}

int				ft_handle_path_spritex(t_file *f, int i)
{
	char	*aux;
	char	*ext;
	int		w;
	int		h;

	aux = first_compro(f, aux);
	aux++;
	if ((f->sprite = open(--aux, O_RDONLY)) < 0)
		ft_handle_error("ERROR: OPEN SPRITE TEXTURE\n");
	else
	{
		f->textures[4] = mlx_xpm_file_to_image(f->mlx, aux, &w, &h);
		f->tdata[4] = (int *)mlx_get_data_addr(f->textures[4],
			&f->bits_per_pixel, &f->size_line, &f->endian);
		close(f->sprite);
	}
	return (f->rtn);
}

int				ft_handle_textures(t_file *f)
{
	if (*f->line == 'N' && *(f->line + 1) == 'O')
		if (ft_handle_path_texture(f, 0) == -1)
			ft_handle_error("Text NO ERROR");
	if (*f->line == 'S' && *(f->line + 1) == 'O')
		if (ft_handle_path_texture(f, 1) == -1)
			ft_handle_error("Text SO ERROR");
	if (*f->line == 'W' && *(f->line + 1) == 'E')
		if (ft_handle_path_texture(f, 2) == -1)
			ft_handle_error("Text WE ERROR");
	if (*f->line == 'E' && *(f->line + 1) == 'A')
		if (ft_handle_path_texture(f, 3) == -1)
			ft_handle_error("Text EA ERROR");
	return (f->rtn);
}

int				ft_handle_spritex(t_file *f)
{
	int i;

	i = 0;
	if (!*f->line && (f->texture[0] >= 3 && f->texture[1] > f->texture[0]
		&& f->texture[2] > f->texture[1]) && !f->sprite)
		f->line++;
	while (*f->line)
	{
		if (*f->line == 'S' && *(f->line + 1) == ' ')
			if (ft_handle_path_spritex(f, i) == -1)
				ft_handle_error("Text S ERROR");
			else
				f->countmap[5]++;
		if (*f->line)
			f->line++;
	}
	return (f->rtn);
}
