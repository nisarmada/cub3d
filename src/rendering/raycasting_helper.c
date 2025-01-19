/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting_helper.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 19:23:47 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/19 20:25:11 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_horizontal_hit(t_ray *r, t_raycasting *rc)
{
	rc->wall_hit_position = (float)fmod(r->ray_y, TILE_SIZE) / TILE_SIZE;
	if (r->dir_x < 0)
	{
		rc->wall_hit_position = 1.0 - rc->wall_hit_position;
		rc->wall_direction = WEST;
	}
	else
		rc->wall_direction = EAST;
}

void	handle_vertical_hit(t_ray *r, t_raycasting *rc)
{
	rc->wall_hit_position = (float)fmod(r->ray_x, TILE_SIZE) / TILE_SIZE;
	if (r->dir_y > 0)
	{
		rc->wall_hit_position = 1.0 - rc->wall_hit_position;
		rc->wall_direction = SOUTH;
	}
	else
		rc->wall_direction = NORTH;
}

bool	check_wall_collision(t_cub *cub, t_ray *r)
{
	return (r->tile_y >= 0 && r->tile_y < cub->map_height
		&& r->tile_x >= 0 && r->tile_x < cub->map_width
		&& cub->map[r->tile_y][r->tile_x] == '1');
}

float	process_ray_hit(t_cub *cub, t_ray *r,
	t_raycasting *rc, bool is_horizontal)
{
	if (check_wall_collision(cub, r))
	{
		if (is_horizontal)
			handle_horizontal_hit(r, rc);
		else
			handle_vertical_hit(r, rc);
		return (calc_ray_distance(cub->player->x, cub->player->y,
				r->ray_x, r->ray_y));
	}
	return (-1);
}
