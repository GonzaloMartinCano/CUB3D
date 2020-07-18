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


/*----------TAMAÑOS TEXTURAS PREDEF---------*/

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define VMOVE 200
# define VDIV 1
# define UDIV 1

/*----------TECLAS_KEYCODE---------*/

#ifdef __linux__
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



typedef struct s_vector
{
	double x;
	double y;
} 				t_vector;

typedef struct		s_sprite
{
	t_vector		pos;						// posicion del sprite en el mapa
	t_vector		cam_pos;					// posicion del sprite en relacion conm la camara
	double			distance;					// distancia del sprite con el jugador
	int				used;						// indica is el sprite ya ha sido pintado
}					t_sprite;

typedef struct 		s_moves
{
	t_vector	dir;	// dirección inicial del vector
	t_vector 	plane; 	// plano de camara
	t_vector	rayDir;
	t_vector	sideDist;			// distancia desde el punto inicial al siguiente lado
	t_vector	deltaDist;	 		//  distancia hasta siguiene lado
	double		time;
	double		oldTime;
	double		cameraX;
	int			mapX;				//  posición inicial del jugador
	int			mapY;
	int			side;				// lado	
	int			stepX;
	int			stepY;
	double		perpWallDist;		// distancia desde nuestra posición a la pared.
	int			lineHeight;			// tamaño de la linea que vamos a dibujar.
	int			drawStart;
	int			drawEnd;
	int			color;
	double		moveSpeed;
	double		rotSpeed;
	int			W;
	int			S;
	int			A;
	int			D;
	int			L;
	int			R;
	int			textX;
	int			textY;	
	double		textpos;
	double		wallX;
	double		textstep;
	int			textside;
}					t_moves;

typedef struct		s_readfile
{
	void	*mlx;
	void	*win;
	int		fd;					//  FD del Mapa.
	int		w;					//  Ancho de Pantalla.
	int		h;					//  Alto de pantalla.
	int		texture[4];			//  Array de FD de Texturas.
								//   [0] NO ./north_texture [1] SO ./south_texture[2]
								//   WE ./west_texture [3] EA ./east_textur
	int		sprite;				//  FD de Spritex.
	char	*line;				//  Linea leida por el GNL.
	char	*c_f;				//  Colores suelo hex
	int		cf[3];				//  colores del suelo en formato rgb.
	char	*c_c;				//  colores del techo en formato hex.
	int		cc[3];
	int		ccieling;		// Color formato int
	int		cfloor;
	int		**map;				//  Matriz de mapa
	char	dir;				//  orientacion del jugador
	int		pos[2];				// 	posicion incial del jugador
	int		mapreaded;			//  -1 si no se ha leido 0 si se termino de leer
	int		nColMax;			//  Numero de columnas MAX
	int		nFil;				//  Numero de filas
	char	*buff;				//  Buff auxiliar para guardar el mapa;
	int		rtn;				//  retorno para funciones, -1 = ERROR;
	void	*img;
	int		*data_img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_vector	currentpos;
	int 	*textures[5];
	int		*tdata[5];
	double			*z_buffer;						// buffer profundidad
	t_sprite		*sp;						// array de estructuras de sprites
	int				*sp_order;					// array de index ordenados
	t_vector		transform;					// transform del sprite
	double			inv_det;					// inversa para transform
	int				sp_screen_x;
	int				sp_height;					// altura del sprite
	int				sp_width;					// ancho del sprite
	int				start_sp_x;					// draw start x
	int				start_sp_y;					// draw start y
	int				end_sp_x;					// draw end x
	int				end_sp_y;					// draw end y
	int				tex_x;						// texture x
	int				tex_y;
	int				sprite_num;
	int				movescreen;
	int				bmp_active; 
	t_moves	m;
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
	int color;
}					t_bmp;

int					ft_read(t_file *f);
int					ft_read_src_file(t_file *f);
void				ft_handle_colors(t_file *f);
void				ft_handle_error(char *str);
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
int 				ft_key_press(int key, t_file *f);
int 				ft_key_release(int key, t_file *f);
int 				ft_movement(t_file *f);
int 				ft_move_draw(t_file *f);
int 				ft_rotation(t_file *f);
int					ft_canmove(int x);
int					ft_exitgame(t_file *f);
void				ft_color_side(t_file *f);
void				ft_sprite(t_file *f);
int 				get_sprite_pos(t_file *f);
void 				ft_init_sp(t_file *f);
void 				ft_calc_dist_draw(t_file *f);
void				ft_init_bmp(t_file *f, t_bmp *bmp);
void				ft_save_bmp(t_file *f);
void 				checkcorrectargument(t_file *f, char *aux);
void 				freeaux(char **aux);


#endif
