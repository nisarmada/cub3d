/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_miniplayer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: elleneklund <elleneklund@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 20:11:20 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 20:11:40 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_cub *cub, mlx_image_t *img, float scale)
{
	int	x;
	int	y;
	int	r;
	int	i;
	int	j;

	x = cub->player->x * scale;
	y = cub->player->y * scale;
	r = (TILE_SIZE * scale) / 4;
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
			{
				mlx_put_pixel(img, x + i, y + j, GREEN);
			}
			j++;
		}
		i++;
	}
}

void	render_fov(t_player *player, t_cub *cub, float scale)
{
	int		max_distance;
	float	left_angle;
	float	right_angle;
	int		x_left;
	int		y_left;
	int		x_right;
	int		y_right;

	(void)cub;
	max_distance = 400;
	left_angle = player->angle + player->fov / 2;
	right_angle = player->angle - player->fov / 2;
	normalize_angle(&left_angle);
	normalize_angle(&right_angle);
	x_left = (int)player->x * (int)scale + cos(left_angle) * max_distance;
	y_left = (int)player->y * (int)scale - sin(left_angle) * max_distance;
	x_right = (int)player->x * (int)scale + cos(right_angle) * max_distance;
	y_right = (int)player->y * (int)scale - sin(right_angle) * max_distance;
	draw_line(cub, x_left, y_left, scale);
	draw_line(cub, x_right, y_right, scale);
}
