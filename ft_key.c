#include "cub3d.h"
#include <math.h>

static int     ft_canmove (int x)
{
    if (x == 1 || x == 2)
        return (0);
    return (1);
}

int ft_movement(t_file *f)
{
    double auxdirX;
    double auxdirY;
    double auxplaneX;
    double auxplaneY;
    if (f->m.W > 0) // W
    {
        if (ft_canmove(f->map[(int)(f->currentpos.x + f->m.dir.x * f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x += f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)f->currentpos.x][(int)(f->currentpos.y + f->m.dir.y * f->m.moveSpeed)]))
			f->currentpos.y += f->m.dir.y * f->m.moveSpeed;
    }
    if (f->m.S > 0) // S
    {
        if (ft_canmove(f->map[(int)(f->currentpos.x - f->m.dir.x * f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x -= f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)f->currentpos.x][(int)(f->currentpos.y - f->m.dir.y * f->m.moveSpeed)]))
			f->currentpos.y -= f->m.dir.y * f->m.moveSpeed;
    }
    if (f->m.A > 0) // A
    {
        if (ft_canmove(f->map[(int)(f->currentpos.x)][(int)(f->currentpos.y + f->m.dir.x * f->m.moveSpeed)]))
			f->currentpos.y += f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)(f->currentpos.x - f->m.dir.y * f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x -= f->m.dir.y * f->m.moveSpeed;
    }
    if (f->m.D > 0) // D
    {
        if (ft_canmove(f->map[(int)(f->currentpos.x)][(int)(f->currentpos.y - f->m.dir.x * f->m.moveSpeed)]))
			f->currentpos.y -= f->m.dir.x * f->m.moveSpeed;
		if (ft_canmove(f->map[(int)(f->currentpos.x + f->m.dir.y * f->m.moveSpeed)][(int)f->currentpos.y]))
			f->currentpos.x += f->m.dir.y * f->m.moveSpeed;
    }
    if (f->m.L > 0) // LEFT
    {
        auxplaneX = f->m.plane.x;
        auxdirX = f->m.dir.x;
        f->m.dir.x = f->m.dir.x * cos(f->m.rotSpeed) - f->m.dir.y * sin(f->m.rotSpeed);
        f->m.dir.y = auxdirX * sin(f->m.rotSpeed) + f->m.dir.y * cos(f->m.rotSpeed);
        auxplaneX = f->m.plane.x;
        f->m.plane.x = f->m.plane.x * cos(f->m.rotSpeed) - f->m.plane.y * sin(f->m.rotSpeed);
        f->m.plane.y = auxplaneX * sin(f->m.rotSpeed) + f->m.plane.y * cos(f->m.rotSpeed);
    }
    if (f->m.R > 0) // RIGHT
    {
        auxplaneX = f->m.plane.x;
        auxdirX = f->m.dir.x;
        f->m.dir.x = f->m.dir.x * cos(-f->m.rotSpeed) - f->m.dir.y * sin(-f->m.rotSpeed);
        f->m.dir.y = auxdirX * sin(-f->m.rotSpeed) + f->m.dir.y * cos(-f->m.rotSpeed);
        auxplaneX = f->m.plane.x;
        f->m.plane.x = f->m.plane.x * cos(-f->m.rotSpeed) - f->m.plane.y * sin(-f->m.rotSpeed);
        f->m.plane.y = auxplaneX * sin(-f->m.rotSpeed) + f->m.plane.y * cos(-f->m.rotSpeed);
    }
    return (0);
}

int ft_key_press(int key, t_file *f)
{
    if (key == KEY_ESC)
        mlx_destroy_window(f->mlx, f->win);
    if (key == KEY_W)
        f->m.W = 1;
    if (key == KEY_S)
        f->m.S = 1;
    if (key == KEY_A)
        f->m.A = 1;
    if (key == KEY_D)
        f->m.D = 1;
    if (key == KEY_LEFT)
        f->m.L = 1;
    if (key == KEY_RIGHT)
        f->m.R = 1;
    return (0);
}

int ft_key_release(int key, t_file *f)
{
    if (key == KEY_ESC)
        mlx_destroy_window(f->mlx, f->win);
    if (key == KEY_W)
        f->m.W = 0;
    if (key == KEY_S)
       f->m.S = 0;
    if (key == KEY_A)
        f->m.A = 0;
    if (key == KEY_D)
        f->m.D = 0;
    if (key == KEY_LEFT)
        f->m.L = 0;
    if (key == KEY_RIGHT)
        f->m.R = 0;
    return (0);
}

int ft_move_draw(t_file *f)
{
    ft_movement(f);
    ft_draw(f);
    return(0);
}