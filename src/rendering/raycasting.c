/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 12:45:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/02 13:15:56 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycasting(t_cub *cub, t_player *player)
{
	normalize_angle(&(player->angle)); // Ensure the angle is within 0 to 2*PI
	cast_single_ray(cub, player, player->angle); //we need to call this in a while loop to do around 1024
	//rays in total from player->angle - player->fov / 2 up to + fov / 2
}

float	cast_single_ray(t_cub *cub, t_player *player, float ray_angle)
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
	float	distance_y; // d3istance to next horizontal border
	float	total_distance;

	// normalize_angle(&ray_angle);
	ray_x = player->x;
	ray_y = player->y;
	dir_x = cos(ray_angle);
	dir_y = -sin(ray_angle);
	tile_x = floor(ray_x / TILE_SIZE);
	tile_y = floor(ray_y / TILE_SIZE);
	distance_x = 0.0;
	distance_y = 0.0;
	total_distance = 0.0;
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
		if (distance_x < distance_y)
		{
			total_distance += distance_x;
			distance_x += delta_x;
			tile_x += step_x; // i need to try to write without step and only check cos sign and then here just add 1
		}
		else
		{
			total_distance += distance_y;
			distance_y += delta_y;
			tile_y += step_y;
		}
		if (cub->map[tile_y][tile_x] == '1' || cub->map[tile_y - 1][tile_x] == '1' || cub->map[tile_y][tile_x - 1] == '1')  // South wall
		{
			draw_line(player, cub->img, tile_x * TILE_SIZE, tile_y * TILE_SIZE);
			return total_distance;
		}
	}
}

