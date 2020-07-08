/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:06:49 by gmartin-          #+#    #+#             */
/*   Updated: 2020/07/08 21:33:43 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Paso 1, leer la resolución:
	posibles errores:
		No existe R
		No puede haber negativos
		Más de dos números || menos de dos números
		mayor que 200px y < 1920 para el ancho
		mayor que 200px y < 1080px para el alto
	Paso 2, leer texturas y guardarlas en un array
	$dir = [NO, SO, WE, EA]
	posibles errores:
		no encuentra $dir[x]
		no encuentra "./"
		Intenta abrir el archivo, crea un array de FD si son válidos
	Paso 3, leer el Sprite
	par amanejar varios archivos tendremos la funcion get_sprites()
	que guarda los FD válidos en un array de enteros. Si existe un invalido
	exit(0);
	posibles errores:
		No encunetra S
		que no encuentra el ./
		que no pueda abrir el archivo de la dirección
		que la extensión de archivos no sea imagen
	Paso 4, leer el color Floor
		hacemo atoi hasta la coma, miramos que el numero sea
		> 0 y < 255, si eso es verdad, le hacemos ft_dec_hex a cada numero
		posibles errores:
			si hay mas de tres numeros, error.
			que alguno de los nuero sea < 0 o > 255
			que sean menos de tres numeros
	Paso 5, leer el color Cielo
		mismas condiciones de paso 4
	Paso 6, leer el mapa
		el mapa sabemos que puede contener 4 caracteres:
			0				espacio vacio
			1				muros
			2				objeto / sprite
			[N, S, E, W]	orientacion inicial del jugador
		posibles errores:
			solo puede tener una sola letra de las validas.
			el mapa debe estar encerrado x muros(1)
				·para comprobar esto utilizamos el algoritmo de flood filling


* */

void	ft_init_file_struct(t_file *f)
{
	int i;

	i = 0;
	f->fd = 0;
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
	f->pos[0] = 1;
	f->pos[1] = 1;
	f->m.stepX = 0;
    f->m.stepY = 0;
    f->m.sideDist.x = 0;
    f->m.sideDist.y = 0;
	f->m.dir.x = 0.0;
	f->m.dir.y = 0.0;
	f->m.rotSpeed = 0.06;
	f->m.moveSpeed = 0.06;
	f->m.side = 0;
	f->m.W  = 0;
	f->m.S = 0;
	f->m.A = 0;
	f->m.D = 0;
	f->m.L = 0;
	f->m.R = 0;
	f->m.textside = 0;
	f->m.textY = 0;
	f->m.textX = 0;
	f->m.textstep = 0;
}

void	ft_handle_error(char *str) //TODO:MODIFICAR STRERR
{
	ft_printf("%s", str);
	exit(0);
}

void		ft_handle_colors(t_file *f)
{
	if ((ft_handle_rgb(f, 1)) == -1)
		ft_handle_error("Text. ERROR while parsing rgb to hex\n");
	if ((ft_handle_rgb(f, 2)) == -1)
		ft_handle_error("Text. ERROR while parsing rgb to hex\n");
}

/*void debugging(t_file *f)
{
	int j = 0;
	int k = 0;
	ft_printf("Res:\n	Ancho: %d\n	Alto: %d\n", f->w, f->h);
	ft_printf("Tex:\n	fd[0]: %d\n	fd[1]: %d\n	fd[2]: %d\n	fd[3]: %d\n", f->texture[0], f->texture[1], f->texture[2], f->texture[3]);
	ft_printf("Spritex:\n	fd: %d\n", f->sprite);
	ft_printf("C_Floor:\n	hexa:	%s\n	c_f[0][R]: %d\n	c_f[1][G]: %d\n	c_f[2][B]: %d\n", f->c_f, f->cf[0], f->cf[1], f->cf[2]);
	ft_printf("C_Roof:\n	hexa:	%s\n	c_c[0][R]: %d\n	c_c[1][G]: %d\n	c_c[2][B]: %d\n", f->c_c, f->cc[0], f->cc[1], f->cc[2]);
	ft_printf("buff:\n%s\n", f->buff);
	ft_printf("posición inicial : (%d : %d) dirección incial: %c\n", f->pos[0], f->pos[1], f->dir);
	ft_printf("\nRTN: %d\n", f->rtn);
	while (j < f->nFil && f->rtn != -1)
    {
        k = 0;
        while (k < f->nColMax)
        {
            ft_printf("%2d", f->map[j][k]);
            k++;
        }
        ft_printf("\n");
        j++;
    }
}*/

int	ft_read(t_file *f)
{
	int			br; //	bytes readed

	ft_init_file_struct(f);
	f->fd = open("tx.txt", O_RDONLY);// TODO:REcibir por argc argv
	while ((br = get_next_line(f->fd, &f->line)) >= 0)
	{
		if (ft_read_src_file(f) == -1)
			return (-1);
		if (br == 0)
			break;
	}
	ft_handle_colors(f);
	alloc_map(f);
	if (f->rtn == -1)
		ft_handle_error("MAP.ERROR while allock. asshole\n");
	if((f->rtn = map_check(f->pos[0], f->pos[1], f)) == -1)
		ft_handle_error("MAP.ERROR while check. stupid\n");
	return (f->rtn);
}

int	main(/*int argc, char *argv[]*/)
{
	t_file		f;  //	Declarar la estructura
	//debugging(&f);
	if(!(f.mlx = mlx_init()))
		ft_handle_error("MAP.ERROR while open_mlx stupid\n");
	ft_read(&f);
	if(!(f.win = mlx_new_window(f.mlx, f.w, f.h, "Hello world!")))
		ft_handle_error("MAP.ERROR while open_mlx_window\n");
	f.img = mlx_new_image(f.mlx, f.w, f.h);
	f.data_img = (int*)mlx_get_data_addr(f.img, &f.bits_per_pixel,
		&f.size_line, &f.endian);
	ft_draw(&f);
	mlx_hook(f.win, 2, 1, ft_key_press, &f);
	mlx_hook(f.win, 3, 2, ft_key_release, &f);
	mlx_loop_hook(f.mlx, ft_move_draw, &f);
	mlx_loop(f.mlx);
	return (0);
}
