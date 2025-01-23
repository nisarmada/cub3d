/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/27 12:45:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 14:45:23 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

float	calc_ray_distance(float x1, float y1, float x2, float y2)
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
	ray->delta_x = TILE_SIZE / fabs(ray->dir_x);
	ray->delta_y = TILE_SIZE / fabs(ray->dir_y);
	if (ray->dir_x > 0)
		ray->step_x = 1;
	else
		ray->step_x = -1;
	if (ray->dir_y > 0)
		ray->step_y = 1;
	else
		ray->step_y = -1;
}

void	calc_start_dist(t_ray *ray)
{
	if (ray->dir_x > 0)
		ray->distance_x = ((ray->tile_x + 1)
				* TILE_SIZE - ray->ray_x) / fabs(ray->dir_x);
	else
		ray->distance_x = (ray->ray_x - TILE_SIZE
				* ray->tile_x) / fabs(ray->dir_x);
	if (ray->dir_y > 0)
		ray->distance_y = ((ray->tile_y + 1)
				* TILE_SIZE - ray->ray_y) / fabs(ray->dir_y);
	else
		ray->distance_y = (ray->ray_y - TILE_SIZE
				* ray->tile_y) / fabs(ray->dir_y);
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

float	cast_single_ray(t_cub *cub, t_raycasting *rc)
{
	t_ray	r;
	float	hit_distance;

	init_param_ray(cub->player, &r, rc->ray_angle);
	calc_start_dist(&r);
	while (1)
	{
		if (r.distance_x < r.distance_y)
		{
			calc_new_dist(&r, 1);
			hit_distance = process_ray_hit(cub, &r, rc, true);
			if (hit_distance >= 0)
				return (hit_distance);
		}
		else
		{
			calc_new_dist(&r, 0);
			hit_distance = process_ray_hit(cub, &r, rc, false);
			if (hit_distance >= 0)
				return (hit_distance);
		}
	}
}
