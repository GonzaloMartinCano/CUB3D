/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:07:03 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/08 20:04:06 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <fcntl.h>
# include "includes/minilibx/mlx.h"
# include "includes/printf/ft_printf.h"
# include <math.h>
# include <X11/Xlib.h>
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define VMOVE 200
# define VDIV 1
# define UDIV 1

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_C 99
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
# else
#  define KEY_ESC 53
#  define KEY_C 8
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125

# endif

typedef struct		s_vector
{
	double x;
	double y;
}					t_vector;

typedef struct		s_sprite
{
	t_vector		pos;
	t_vector		cam_pos;
	double			distance;
	int				used;
}					t_sprite;

typedef struct		s_moves
{
	t_vector	dir;
	t_vector	plane;
	t_vector	raydir;
	t_vector	sidedist;
	t_vector	deltadist;
	double		camerax;
	int			mapx;
	int			mapy;
	int			side;
	int			stepx;
	int			stepy;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			color;
	double		movespeed;
	double		rotspeed;
	int			w;
	int			s;
	int			a;
	int			d;
	int			l;
	int			r;
	int			textx;
	int			texty;
	double		textpos;
	double		wallx;
	double		textstep;
	int			textside;
}					t_moves;

typedef struct		s_readfile
{
	void		*mlx;
	void		*win;
	int			fd;
	int			w;
	int			h;
	int			texture[4];
	int			sprite;
	char		*line;
	char		*c_f;
	int			cf[3];
	char		*c_c;
	int			cc[3];
	int			ccieling;
	int			cfloor;
	int			**map;
	char		dir;
	int			pos[2];
	int			mapreaded;
	int			ncolmax;
	int			nfil;
	char		*buff;
	int			rtn;
	void		*img;
	int			*data_img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	t_vector	currentpos;
	int			*textures[5];
	int			*tdata[5];
	double		*z_buffer;
	t_sprite	*sp;
	int			*sp_order;
	t_vector	transform;
	double		inv_det;
	int			sp_screen_x;
	int			sp_height;
	int			sp_width;
	int			start_sp_x;
	int			start_sp_y;
	int			end_sp_x;
	int			end_sp_y;
	int			tex_x;
	int			tex_y;
	int			sprite_num;
	int			movescreen;
	int			bmp_active;
	t_moves		m;
}					t_file;

typedef struct		s_bmp
{
	unsigned char	type[2];
	int				file_size;
	int				reserved;
	int				offset;
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
	int				color;
}					t_bmp;

int					ft_read(t_file *f);
int					ft_read_src_file(t_file *f);
void				ft_handle_colors(t_file *f);
void				ft_handle_error(char *str);
void				ft_handle_error2(char *str, char *aux, t_file *f);
int					ft_handle_rgb(t_file *f);
int					ft_handle_resolution(t_file *f);
int					ft_check_extension(char *str);
int					ft_handle_textures(t_file *f);
int					ft_handle_spritex(t_file *f);
int					ft_handle_cfloor(t_file *f);
int					ft_handle_croof(t_file *f);
int					ft_handle_map_read(t_file *f);
int					alloc_map(t_file *f);
int					map_check(int row, int col, t_file *f);
int					ft_calcdirns(t_file *f);
int					ft_calcdirew(t_file *f);
void				ft_hit_wall(t_file *f);
void				ft_wall_height(t_file *f);
void				ft_color(t_file *f);
void				ft_config_texture(t_file *f);
int					ft_draw(t_file *m);
int					ft_key_press(int key, t_file *f);
int					ft_key_release(int key, t_file *f);
int					ft_movement(t_file *f);
int					ft_move_draw(t_file *f);
int					ft_rotation(t_file *f);
int					ft_canmove(int x);
int					ft_exitgame(t_file *f);
void				ft_color_side(t_file *f);
void				ft_sprite(t_file *f);
int					get_sprite_pos(t_file *f);
void				ft_init_sp(t_file *f);
void				ft_calc_dist_draw(t_file *f);
void				ft_init_bmp(t_file *f, t_bmp *bmp);
void				ft_save_bmp(t_file *f);
void				checkcorrectargument(t_file *f, char *aux);
void				freeaux(char **aux);

#endif
