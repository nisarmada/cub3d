/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 19:46:05 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/19 19:55:49 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_line_1(t_line *line, t_cub *cub, float scale)
{
	line->x0 = cub->player->x * scale;
	line->y0 = cub->player->y * scale;
}

void	init_line_2(t_line *line, int dest_x, int dest_y)
{
	line->x = dest_x;
	line->y = dest_y;
	line->dx = abs(dest_x - line->x0);
	line->dy = abs(dest_y - line->y0);
	line->err = line->dx - line->dy;
}

void	init_line_direction(t_line *line)
{
	if (line->x > line->x0)
		line->sx = 1;
	else
		line->sx = -1;

	if (line->y > line->y0)
		line->sy = 1;
	else
		line->sy = -1;
}


void	draw_line_pixel(t_line *line, t_cub *cub)
{
	if (line->x0 >= 0 && line->x0 < cub->win_width
		&& line->y0 >= 0 && line->y0 < cub->win_height)
	{
		mlx_put_pixel(cub->img, line->x0, line->y0, GREEN);
	}
}

void	update_line_position(t_line *line)
{
	int	err2;

	err2 = line->err * 2;
	if (err2 > -line->dy)
	{
		line->err -= line->dy;
		line->x0 += line->sx;
	}
	if (err2 < line->dx)
	{
		line->err += line->dx;
		line->y0 += line->sy;
	}
}

