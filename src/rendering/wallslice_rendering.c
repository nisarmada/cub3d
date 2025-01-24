/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wallslice_rendering.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 13:27:52 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/23 17:22:18 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static mlx_texture_t	*wall_texture_direction(t_cub *cub,
	t_wall_direction *wall_direction)
{
	if (*wall_direction == NORTH)
		return (cub->text->no);
	else if (*wall_direction == SOUTH)
		return (cub->text->so);
	else if (*wall_direction == WEST)
		return (cub->text->we);
	else if (*wall_direction == EAST)
		return (cub->text->ea);
	return (cub->text->no);
}

//Determines where on the screen to start and stop drawing the wall
static void	calc_y_interval(t_slice *slice, int win_height, float line_height)
{
	slice->start_y = (win_height / 2) - ((int)line_height / 2);
	slice->end_y = (win_height / 2) + ((int)line_height / 2);
	if (slice->start_y < 0)
		slice->start_y = 0;
	if (slice->end_y >= win_height)
		slice->end_y = win_height - 1;
}

static void	init_slice_text(t_raycasting *rc, mlx_texture_t *texture, \
t_slice *slice, int win_height)
{
	rc->text_x = (int)(rc->wall_hit_position * texture->width) % texture->width;
	slice->step = 1.0 * texture->height / rc->line_height;
	slice->text_pos = (slice->start_y - win_height / 2 + rc->line_height / 2) * \
	slice->step;
	slice->y = slice->start_y;
}

static void	draw_wall_pixel(t_cub *cub, t_raycasting *rc, \
t_slice *slice, mlx_texture_t *texture)
{
	rc->text_y = (int)slice->text_pos & (texture->height - 1);
	slice->text_pos += slice->step;
	slice->color = get_texture_color(cub, texture, rc);
	mlx_put_pixel(cub->img, rc->x, slice->y, slice->color);
}

void	render_wallslice(t_cub *cub, t_raycasting *rc)
{
	t_slice			slice;
	mlx_texture_t	*texture;

	rc->line_height = (TILE_SIZE / rc->correct_dist) * cub->dist_pplane;
	texture = wall_texture_direction(cub, &rc->wall_direction);
	calc_y_interval(&slice, cub->win_height, rc->line_height);
	init_slice_text(rc, texture, &slice, cub->win_height);
	while (slice.y < slice.end_y)
	{
		draw_wall_pixel(cub, rc, &slice, texture);
		slice.y++;
	}
}
