/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 18:41:18 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/12 14:28:28 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*OPTIMIZATION
Optimize Loops:

    Avoid redundant operations in nested loops by caching results or breaking early when possible.

Memory Cleanup:

    Ensure all dynamically loaded resources are freed appropriately to avoid memory leaks.
*/


void draw_tile(mlx_image_t *img, int x, int y, float scale, int color)
{
	int i;
	int j;

	i = 0;
	while (i < (TILE_SIZE * scale))
	{
		j = 0;
		while (j < (TILE_SIZE * scale))
		{
			mlx_put_pixel(img, x + i, j + y, color);
			j++;
		}
		i++;
	}
}

float render_map(mlx_image_t *img, t_cub *cub)
{
	int		row;
	int		column;
	int		tile_x;
	int		tile_y;
	float	scale_x;
	float	scale_y;
	float	scale;
	int		color;

	scale_x = (float)300 / (cub->map_width * TILE_SIZE);
	scale_y = (float)200 / (cub->map_height * TILE_SIZE);
	scale = fminf(scale_x, scale_y);
	row = 0;
	while (row < cub->map_height)
	{
		column = 0;
		while (column < cub->map_width)
		{
			tile_x = column * TILE_SIZE * scale;
			tile_y = row * TILE_SIZE * scale;
			if (cub->map[row][column] == '1') //wall
				color = WALL_COLOR;
			else if (cub->map[row][column] == '0')
				color = FLOOR_COLOR;
			else if (cub->map[row][column] == ' ')
				color = INACCESSIBLE_COLOR;
			else if (cub->map[row][column] == 'N' || cub->map[row][column] == 'S' || 
                     cub->map[row][column] == 'E' || cub->map[row][column] == 'W')
				color = FLOOR_COLOR;
			draw_tile(img, tile_x, tile_y, scale, color);
			column++;
		}
		row++;
	}
	// render_dir(cub->player, img, cub, scale);
	render_fov(cub->player, img, cub, scale);
	// raycasting(cub, cub->player);
	return (scale);
}

void render_player(t_cub *cub, mlx_image_t *img, float scale)
{
	int x;
	int y;
	int r;
	int i;
	int j;

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
	// render_fov(cub->player, img);
}

// void render_dir(t_player *player, mlx_image_t *img, t_cub *cub, float scale)
// {

// }


void render_fov(t_player *player, mlx_image_t *img, t_cub *cub, float scale)
{
	int max_distance;
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
	draw_line(player, img, x_left, y_left, scale);
	draw_line(player, img, x_right, y_right, scale);
	// raycasting(cub, cub->player);
}

