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
	perror(str);
	exit(0);
}

void			ft_handle_error2(char *str, char *aux, t_file *f)
{
	if (aux)
		free(aux);
	perror(str);
	ft_exitgame(f);
}

int				ft_handle_rgb(t_file *f)
{
	f->ccieling = (((f->cc[0] * 256) * 256) + (f->cc[1] * 256) + f->cc[2]);
	f->cfloor = (((f->cf[1] * 256) * 256) + (f->cf[1] * 256) + f->cf[2]);
	if (f->ccieling < 0 || f->cfloor < 0)
		ft_handle_error("ERROR color");
}

int				ft_read_src_file(t_file *f)
{
	if (f->line[0] == 'R' && f->line[1] == ' ')
		f->rtn = ft_handle_resolution(f);
	else if ((f->line[0] == 'N' && f->line[1] == 'O') || (f->line[0] == 'S' &&
		f->line[1] == 'O') || (f->line[0] == 'W' && f->line[1] == 'E') ||
		(f->line[0] == 'E' && f->line[1] == 'A'))
		f->rtn = ft_handle_textures(f);
	else if (f->line[0] == 'S' && f->line[1] == ' ')
		f->rtn = ft_handle_spritex(f);
	else if (f->line[0] == 'F' && f->line[1] == ' ')
		f->rtn = ft_handle_cfloor(f);
	else if (f->line[0] == 'C' && f->line[1] == ' ')
		f->rtn = ft_handle_croof(f);
	else if (ft_isdigit(f->line[0]) || f->line[0] == ' ')
		f->rtn = ft_handle_map_read(f);
	else if (ft_isspace(f->line) == (int)ft_strlen(f->line))
		f->rtn = 1;
	else
		ft_handle_error("ERROR: CONFIG LINE FORBIDEN\n");
	return (f->rtn);
}
