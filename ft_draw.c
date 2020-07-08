#include "cub3d.h"

int ft_calcdir(t_file *f)
{
    if (f->dir == 'N')
    {
        f->m.dir.x = -1.0;
        f->m.dir.y = 0.0;
        f->m.plane.x = 0.0;
        f->m.plane.y = 0.66;
    }
    else if (f->dir == 'S')
    {
        f->m.dir.x = 1.0;
        f->m.dir.y = 0.0;
        f->m.plane.x = 0.0;
        f->m.plane.y = -0.66;
    }
    else if (f->dir == 'E')
    {
        f->m.dir.x = 0.0;
        f->m.dir.y = 1.0;
        f->m.plane.x = 0.66;
        f->m.plane.y = 0.00;
    }
    else if (f->dir == 'W')
    {
        f->m.dir.x = 0.0;
        f->m.dir.y = -1.0;
        f->m.plane.x = -0.66;
        f->m.plane.y = 0.00;
    }
}

int ft_calcstep(t_file *f)
{
    if (f->m.rayDir.x < 0)
    {
        f->m.stepX = -1;
        f->m.sideDist.x = (f->currentpos.x - f->m.mapX) * f->m.deltaDist.x;
    }
    else
    {
        f->m.stepX = 1;
        f->m.sideDist.x = (f->m.mapX + 1.0 - f->currentpos.x) * f->m.deltaDist.x;
    }
    if (f->m.rayDir.y < 0)
    {
        f->m.stepY = -1;
        f->m.sideDist.y = (f->currentpos.y - f->m.mapY) * f->m.deltaDist.y;
    }
    else
    {
        f->m.stepY = 1;
        f->m.sideDist.y = (f->m.mapY + 1.0 - f->currentpos.y) * f->m.deltaDist.y;
    }
}
void ft_color_side(t_file *f)
{
    double	dx;
	double	dy;

	dx = f->m.mapX - f->currentpos.x;
	dy = f->m.mapY - f->currentpos.y;
    if (dx < 0 && f->m.side == 0)       // Textura S (cuando miramos al N)
        f->m.textside = 3;
    if (dx > 0 && f->m.side == 0)       // Textura N
       f->m.textside = 2;
    if (dy < 0 && f->m.side == 1)       // Textura E (cuando miramos al W)
        f->m.textside = 1;
    if (dy > 0 && f->m.side == 1)       // Textura W
        f->m.textside = 0;
}
static int ft_color(t_file *f)
{
    int color;
    if (f->map[f->m.mapX][f->m.mapY] == 1)
        ft_color_side(f);
    if (f->map[f->m.mapX][f->m.mapY] == 2)
        color = 16712447;
    return (color);
}

void	ft_config_texture(t_file *f)
{
	if (f->m.side == 0)
		f->m.wallX = f->currentpos.y + f->m.perpWallDist * f->m.rayDir.y;
	else
		f->m.wallX = f->currentpos.x + f->m.perpWallDist * f->m.rayDir.x;
	f->m.wallX -= floor(f->m.wallX);
	f->m.textX = (int)(f->m.wallX * (double)TEXTURE_WIDTH);
	if (f->m.side == 0 && f->m.rayDir.x > 0)
		f->m.textX = TEXTURE_WIDTH - f->m.textX - 1;
	if (f->m.side == 1 && f->m.rayDir.y < 0)
		f->m.textX = TEXTURE_WIDTH - f->m.textX - 1;
	f->m.textstep = 1.0 * TEXTURE_HEIGHT / f->m.lineHeight;
	f->m.textpos = (f->m.drawStart - f->h / 2 + f->m.lineHeight / 2) * f->m.textstep;
}

void ft_draw_line(t_file *f, int x)
{
    int i = 0;
    int color;
    while (i < f->m.drawStart)
	{
		*(f->data_img + (i * f->w) + x) = 7719150;
		i++;
	}
    while (i < f->m.drawEnd)
    {
        f->m.textY = (int)f->m.textpos & (TEXTURE_HEIGHT - 1);
		f->m.textpos += f->m.textstep;
		color = f->tdata[f->m.textside][TEXTURE_HEIGHT * f->m.textY + f->m.textX];
		*(f->data_img + (i * f->w) + x) = color;
		i++;
    }
    while (i < f->h)
    {
        *(f->data_img + (i * f->w) + x) = 7364912;
		i++;
    }
}

int ft_draw(t_file *f)
{
    int hit;
    int x;
    x = 0;
    // calculo de camera e inicio rayos
    while (x < f->w)
    {
        hit = 0;
        f->m.mapX = f->currentpos.x;
        f->m.mapY = f->currentpos.y;
        f->m.cameraX = (2 * x / (double)f->w) - 1;
        f->m.rayDir.x = f->m.dir.x + f->m.plane.x * f->m.cameraX;
        f->m.rayDir.y = f->m.dir.y + f->m.plane.y * f->m.cameraX;
        f->m.deltaDist.x = (f->m.rayDir.y == 0) ? 0 : ((f->m.rayDir.x == 0) ? 1 : fabs(1 / f->m.rayDir.x));
        f->m.deltaDist.y = (f->m.rayDir.x == 0) ? 0 : ((f->m.rayDir.y == 0) ? 1 : fabs(1 / f->m.rayDir.y));
        ft_calcstep(f);
        while (hit == 0)
        {   
            if (f->m.sideDist.x < f->m.sideDist.y)
            {
                f->m.sideDist.x += f->m.deltaDist.x;
                f->m.mapX += f->m.stepX;
                f->m.side = 0;
            }
            else
            {
                f->m.sideDist.y += f->m.deltaDist.y;
                f->m.mapY += f->m.stepY;
                f->m.side = 1;
            }
            if (f->map[f->m.mapX][f->m.mapY] == 2 || f->map[f->m.mapX][f->m.mapY] == 1)
                hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (f->m.side == 0)
            f->m.perpWallDist = (f->m.mapX - f->currentpos.x + (1 - f->m.stepX) / 2) / f->m.rayDir.x;
        else
            f->m.perpWallDist = (f->m.mapY - f->currentpos.y + (1 - f->m.stepY) / 2) / f->m.rayDir.y;
        //Calculate height of line to draw on screen
        f->m.lineHeight = (int)(f->h / f->m.perpWallDist) * 2;
        //calculate lowest and highest pixel to fill in current stripe
        f->m.drawStart = (-f->m.lineHeight / 2) + f->h / 2;
        if (f->m.drawStart < 0)
            f->m.drawStart = 0;
        f->m.drawEnd = (f->m.lineHeight / 2) + f->h / 2;
        if (f->m.drawEnd >= f->h || f->m.drawEnd <= 0)
            f->m.drawEnd = f->h - 1;
        //choose wall color
        f->m.color = ft_color(f);
        ft_config_texture(f);
        ft_draw_line(f, x);
        x++;
    }
    mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
//}