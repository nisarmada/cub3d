/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extras.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:59:53 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/19 15:33:34 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void normalize_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

// void normalize_angle(float *angle)
// {
//     while (*angle < 0)
//         *angle += 2 * M_PI;
//     while (*angle > 2 * M_PI)
//         *angle -= 2 * M_PI;
// }


void draw_line(t_cub *cub, int x, int y, float scale)
{
	int dx;
	int	dy;
	int sx;
	int	sy;
	int x0;
	int y0;
	int err;
	int	err2;

	x0 = cub->player->x * scale;
	y0 = cub->player->y * scale;
	dx = abs(x - x0); // x1 - x0
	dy = abs(y - y0); // y1 - y0
	err = dx - dy;
	if (x > x0)
		sx = 1;
	else
		sx = -1;
	if (y > y0)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		if (x0 >= 0 && x0 < cub->win_width  && y0 >= 0 && y0 < cub->win_height)
			mlx_put_pixel(cub->img, x0, y0, GREEN);

		if (x0 == x && y0 == y)
			break;

		err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_line_float(t_player *player, mlx_image_t *img, int x, int y, float scale)
{
	float dx;
	float dy;
	float x0;
	float y0;
	float sx;
	float sy;
	float err;
	float err2;

	x0 = player->x * scale;
	y0 = player->y * scale;
	dx = x - x0;
	dy = y - y0;
	if (x > x0)
		sx = 1.0;
	else
		sx = -1.0;
	if (y > y0)
		sy = 1.0;
	else
		sy = -1.0;
	err = dx - dy;
	while (1)
	{
		if (x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 600)
        {
            mlx_put_pixel(img, (int)x0, (int)y0, GREEN);
        }
		if ((int)x0 == (int)x && (int)y0 == (int)y)
			break;
		err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}