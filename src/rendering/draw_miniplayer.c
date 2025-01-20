/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_miniplayer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 20:11:20 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/20 12:17:42 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

float	calculate_scale(int map_width, int map_height)
{
	t_coord	scale_coord;
	float	scale;

	scale_coord.x = (float)300 / (map_width * TILE_SIZE);
	scale_coord.y = (float)200 / (map_height * TILE_SIZE);
	scale = fminf(scale_coord.x, scale_coord.y);
	return (scale);
}

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
	t_coord	left;
	t_coord	right;

	(void)cub;
	max_distance = 400;
	left_angle = player->angle + player->fov / 2;
	right_angle = player->angle - player->fov / 2;
	normalize_angle(&left_angle);
	normalize_angle(&right_angle);
	left.x = (int)player->x * (int)scale + cos(left_angle) * max_distance;
	left.y = (int)player->y * (int)scale - sin(left_angle) * max_distance;
	right.x = (int)player->x * (int)scale + cos(right_angle) * max_distance;
	right.y = (int)player->y * (int)scale - sin(right_angle) * max_distance;
	draw_line(cub, (int)left.x, (int)left.y, scale);
	draw_line(cub, (int)right.x, (int)right.y, scale);
}
