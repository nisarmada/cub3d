/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 12:45:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/04 17:29:38 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void raycasting(t_cub *cub, t_player *player)
{
	float	distorted_distance;
	float	correct_dist;
	float	div;
	// float	ray_angle;
	int		x;
	int		y;

	x = 0;
	while (x < WIN_WIDTH) 
	{
		// Render the ceiling (top half of the screen)
		y = 0;
		while (y < WIN_HEIGHT / 2) {
			mlx_put_pixel(cub->img, x, y, RED);
			y++;
		}
		// Render the floor (bottom half of the screen)
		y = WIN_HEIGHT / 2;
		while (y < WIN_HEIGHT) {
			mlx_put_pixel(cub->img, x, y, GREEN);
			y++;
		}
		x++;
	}
	div = -M_PI / 6;
	float step = (M_PI / 3) / WIN_WIDTH;
	while (div <= M_PI / 6)
	{
		// ray_angle = player->angle + div;
		// normalize_angle(&(ray_angle)); // Ensure the angle is within -2PI to 2*PI
		// distorted_distance = cast_single_ray(cub, player, ray_angle);
		normalize_angle(&(player->angle)); // Ensure the angle is within 0 to 2*PI
		distorted_distance = cast_single_ray(cub, player, player->angle + div); // 
		correct_dist = distorted_distance * cos(div);
		int x = (div + M_PI / 6) / step;
		render_wallslice(cub, correct_dist, player->angle + div, x);
		div += step;
	}
}

// void raycasting(t_cub *cub, t_player *player)
// {
// 	float	distorted_distance;
// 	float	correct_dist;
// 	float	one_degree_in_rad;
// 	int		r;
// 	float	ray_angle;

// 	one_degree_in_rad = 0.0174532925;
// 	r = 0;
// 	ray_angle =  player->angle - one_degree_in_rad*30;
// 	while (r < 60)
// 	{
// 		normalize_angle(&(player->angle)); // Ensure the angle is within -2PI to 2*PI
// 		normalize_angle(&(ray_angle));
// 		distorted_distance = cast_single_ray(cub, player, ray_angle); //we need to call this in a while loop to do around 1024
// 		correct_dist = distorted_distance * cos(player->angle - ray_angle);
// 		// render_wallslice(cub, correct_dist, player->angle + div);
// 		ray_angle += one_degree_in_rad;
// 		r++;
// 	}
// 	printf("distorted: %f, corrected: %f\n", distorted_distance, correct_dist);
// 	//rays in total from player->angle - player->fov / 2 up to + fov / 2
// }

/*
projection plan: 
distance from player to projection plan = (projectionplan width / 2) / tan(30 (half of fov))
angle between rays = fov / projectionplan width (these are columns on the projection plan)
projected wall slice height = actual wall slice height / dist to the actual wall * dist f. player to projection plane
projected wall slice height = 32 / correct_dist * dist f. player to projection plane
draw vertical line on the corresponding column on projection plane
*/

// void	draw_minimap(t_cub *cub, t_player *player)
// {
// 	int scaled_tile;
// 	int	y;
// 	int	x;

// 	scaled_tile = TILE_SIZE * MINIMAP_SCALE;
// 	while (y < cub->map_height)
// 	{
// 		x = 0;
// 		while (x < cub->map_width)
// 		{
			
// 		}
// 	}
// }

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
		// if (tile_x < 0 || tile_x >= cub->map_width || tile_y < 0 || tile_y >= cub->map_height)
		// 	break;
		if (cub->map[tile_y][tile_x] == '1' || cub->map[tile_y - 1][tile_x] == '1' || cub->map[tile_y][tile_x - 1] == '1')  // South wall
		{
			draw_line(player, cub->img, tile_x * TILE_SIZE, tile_y * TILE_SIZE);
			return (total_distance);
		}
	}
	// return (1);
}

