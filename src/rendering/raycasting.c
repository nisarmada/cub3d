/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 12:45:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/27 18:08:32 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycasting(t_cub *cub, t_player *player)
{
	// t_raycast result;
	// float ray;

	normalize_angle(&player->angle);
	// ray = player->angle;
	//  printf("Raycasting - Player Angle: %.2f\n", player->angle);
	cast_single_ray(cub, cub->player, player->angle);
	// draw_line(player, cub->img, result.tile_x, result.tile_y);
}

t_raycast	cast_single_ray(t_cub *cub, t_player *player, float ray_angle)
{
	float	ray_x; // starting position x
	float	ray_y; // starting poisition y
	float	dir_x; // direction in x axis
	float	dir_y; // direction in y axis
	int		tile_x; // tile normalization
	int		tile_y;
	int		step_x; // determine if we're moving in x or y axis
	int		step_y;
	float	delta_x; // differential with respect to x
	float	delta_y;
	float	distance_x; //distance to next vertical border
	float	distance_y; // distance to next horizontal border
	t_raycast result;

	printf("Player Position: (%i, %i)\n", player->x, player->y);
    printf("Player Angle: %.2f\n", player->angle);
    printf("Ray Angle: %.2f\n", ray_angle);
	ray_x = player->x;
	ray_y = player->y;
	dir_x = cos(ray_angle);
	dir_y = sin(ray_angle);
	tile_x = floor(ray_x / TILE_SIZE);
	tile_y = floor(ray_y / TILE_SIZE);
	distance_x = 0.0;
	distance_y = 0.0;
	if (dir_x > 0)
		step_x = 1; // we move right
	else
		step_x = -1; // we move left
	if (dir_y > 0)
		step_y = 1; // we move down
	else
		step_y = -1; // we move up
	delta_x = TILE_SIZE / fabs(dir_x); // from: cos(x) = TILE_SIZE / dx
	delta_y = TILE_SIZE / fabs(dir_y);
	if (step_x > 0) // we can also say if cos(x) > 0
		distance_x = ((tile_x + 1) * TILE_SIZE - ray_x) / fabs(dir_x);
	else 
		distance_x = (ray_x - TILE_SIZE * tile_x) / fabs(dir_x);		// why do we have different formulas for different directions?

	if (step_y > 0)
		distance_y = ((tile_y + 1) * TILE_SIZE - ray_y) / fabs(dir_y);
	else
		distance_y = (ray_y - TILE_SIZE * tile_y) / fabs(dir_y);
	while (1)
	{
		if (distance_x > distance_y)
		{
			tile_x += step_x; // i need to try to write without step and only check cos sign and then here just add 1
			distance_x += delta_x;
		}
		else
		{
			tile_y += step_y;
			distance_y += delta_y;
		}
		if (cub->map[tile_y][tile_x] == '1')
		{
			result.distance = (distance_x > distance_y) ? distance_x : distance_y;
            result.tile_x = tile_x * TILE_SIZE;
            result.tile_y = tile_y * TILE_SIZE;
			draw_line(player, cub->img, result.tile_x, result.tile_y);
			return (result);
		}
	}
}
