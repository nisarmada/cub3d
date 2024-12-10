/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 12:45:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/10 18:44:52 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* OPTIMIZATION
all calcs that are same every rendering should be caluclated only once!
Reduce Trigonometric Overhead:

    Precompute sine and cosine values for angles if they are reused across frames.

Optimize Ray Distance Calculation:

    Use efficient algorithms for grid traversal (e.g., Digital Differential Analyzer (DDA)).

Boundary Checks:

    Ensure rays terminate when they leave the map bounds to avoid unnecessary calculations.
*/


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

typedef struct s_ray
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
}	t_ray;

static float	calc_ray_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	init_param_ray(t_player *player, t_ray *ray, float ray_angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->dir_x = cos(ray_angle);
	ray->dir_y = -sin(ray_angle);
	ray->tile_x = floor(ray->ray_x / TILE_SIZE);
	ray->tile_y = floor(ray->ray_y / TILE_SIZE);
	ray->distance_x = 0.0;
	ray->distance_y = 0.0;
	ray->delta_x = TILE_SIZE / fabs(ray->dir_x); // from: cos(x) = TILE_SIZE / dx
	ray->delta_y = TILE_SIZE / fabs(ray->dir_y);
	if (ray->dir_x > 0)
		ray->step_x = 1; // we move right
	else
		ray->step_x = -1; // we move left
	if (ray->dir_y > 0)
		ray->step_y = 1; // we move down
	else
		ray->step_y = -1; // we move up

}

void	calc_start_dist(t_ray *ray)
{
	if (ray->dir_x > 0) // we can also say if cos(x) > 0
		ray->distance_x = ((ray->tile_x + 1) * TILE_SIZE - ray->ray_x) / fabs(ray->dir_x);
	else 
		ray->distance_x = (ray->ray_x - TILE_SIZE * ray->tile_x) / fabs(ray->dir_x);		// why do we have ray->different formulas for ray->different ray->directions?
	if (ray->dir_y > 0)
		ray->distance_y = ((ray->tile_y + 1) * TILE_SIZE - ray->ray_y) / fabs(ray->dir_y);
	else
		ray->distance_y = (ray->ray_y - TILE_SIZE * ray->tile_y) / fabs(ray->dir_y);
}

void	calc_new_dist(t_ray *r, int is_x)
{
	if (is_x)
	{
		r->tile_x += r->step_x;
		r->ray_x += r->distance_x * r->dir_x;
		r->ray_y += r->distance_x * r->dir_y;
		r->distance_y -= r->distance_x;
		r->distance_x = r->delta_x;
	}
	else
	{
		r->tile_y += r->step_y;
		r->ray_x += r->distance_y * r->dir_x;
		r->ray_y += r->distance_y * r->dir_y;
		r->distance_x -= r->distance_y;
		r->distance_y = r->delta_y;
	}
	
}

float	cast_single_ray(t_cub *cub, t_player *player, float ray_angle)
{
	t_ray	r;

	init_param_ray(player, &r, ray_angle);
	calc_start_dist(&r);
	while (1)
	{
		if (r.distance_x < r.distance_y)
			calc_new_dist(&r, 1);
		else
			calc_new_dist(&r, 0);
		// if (tile_x < 0 || tile_x >= cub->map_width || tile_y < 0 || tile_y >= cub->map_height)
		// 	break;
		if (cub->map[r.tile_y][r.tile_x] == '1')  // South wall
		{
			// draw_line(player, cub->img, r.tile_x * TILE_SIZE, r.tile_y * TILE_SIZE);
			return (calc_ray_distance(player->x, player->y, r.ray_x, r.ray_y));
		}
	}
	// return (1);

}
