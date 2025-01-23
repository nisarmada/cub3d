/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/23 14:41:10 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	render_view(t_cub *cub, t_player *player)
{
	t_raycasting	rc;
	float			div;
	float			step;

	render_floor_ceiling(cub);
	div = -M_PI / 6;
	step = (M_PI / 3) / cub->win_width;
	rc.x = 0;
	while (rc.x < cub->win_width)
	{
		rc.ray_angle = player->angle + div;
		normalize_angle(&(rc.ray_angle));
		rc.distorted_distance = cast_single_ray(cub, &rc);
		rc.correct_dist = rc.distorted_distance * cos(div);
		rc.line_height = (TILE_SIZE / rc.correct_dist) * cub->dist_pplane;
		render_wallslice(cub, &rc);
		div += step;
		rc.x++;
	}
}

void	render_floor_ceiling(t_cub *cub)
{
	int		x;
	int		y;

	x = 0;
	while (x < cub->win_width)
	{
		y = 0;
		while (y < cub->win_height / 2)
		{
			mlx_put_pixel(cub->img, x, y, cub->wall_color);
			y++;
		}
		y = cub->win_height / 2;
		while (y < cub->win_height)
		{
			mlx_put_pixel(cub->img, x, y, cub->floor_color);
			y++;
		}
		x++;
	}
}
