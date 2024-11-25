/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extras.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:59:53 by nikos         #+#    #+#                 */
/*   Updated: 2024/11/25 13:24:04 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void normalize_angle(float *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

void draw_line(t_player *player, mlx_image_t *img, int x, int y)
{
	int dx;
	int	dy;
	int sx;
	int	sy;
	int x0;
	int y0;
	int err;
	int	err2;

	x0 = player->x;
	y0 = player->y;
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
		if (x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 600)
			mlx_put_pixel(img, x0, y0, GREEN);
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
