/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 18:41:18 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/10 18:42:13 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*OPTIMIZATION
Optimize Loops:

    Avoid redundant operations in nested loops by caching results or breaking early when possible.

Memory Cleanup:

    Ensure all dynamically loaded resources are freed appropriately to avoid memory leaks.
*/


void draw_tile(mlx_image_t *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE * MINIMAP_SCALE)
	{
		j = 0;
		while (j < TILE_SIZE * MINIMAP_SCALE)
		{
			mlx_put_pixel(img, x + i, j + y, color);
			j++;
		}
		i++;
	}
}

void render_map(mlx_image_t *img, t_cub *cub)
{
	int row;
	int column;
	int	tile_x;
	int	tile_y;

	row = 0;
	while (cub->map[row])
	{
		column = 0;
		while (column < cub->map_width)
		{
			tile_x = column * MINI_TILE;
			tile_y = row * MINI_TILE;
			if (cub->map[row][column] == '1') //wall
				draw_tile(img, tile_x, tile_y, WALL_COLOR);
			else if (cub->map[row][column] == '0')
				draw_tile(img, tile_x, tile_y, FLOOR_COLOR);
			else if (cub->map[row][column] == ' ')
				draw_tile(img, tile_x, tile_y, INACCESSIBLE_COLOR);
			else if (cub->map[row][column] == 'N' || cub->map[row][column] == 'S' || 
                     cub->map[row][column] == 'E' || cub->map[row][column] == 'W')
				draw_tile(img, tile_x, tile_y, FLOOR_COLOR);
				
			column++;
		}
		row++;
	}
	render_fov(cub->player, img, cub);
	// raycasting(cub, cub->player);
}

void render_player(t_cub *cub, mlx_image_t *img)
{
	int x;
	int y;
	int r;
	int i;
	int j;

	x = cub->player->x * MINIMAP_SCALE;
	y = cub->player->y * MINIMAP_SCALE;
	r = (TILE_SIZE * MINIMAP_SCALE) / 4;
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

void render_fov(t_player *player, mlx_image_t *img, t_cub *cub)
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
	x_left = (int)player->x * MINIMAP_SCALE + cos(left_angle) * max_distance;
	y_left = (int)player->y * MINIMAP_SCALE - sin(left_angle) * max_distance;
	x_right = (int)player->x * MINIMAP_SCALE + cos(right_angle) * max_distance;
	y_right = (int)player->y * MINIMAP_SCALE - sin(right_angle) * max_distance;
	draw_line(player, img, x_left, y_left);
	draw_line(player, img, x_right, y_right);
	// raycasting(cub, cub->player);
}

