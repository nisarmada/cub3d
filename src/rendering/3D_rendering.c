/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/19 19:13:35 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// correct_dist = distorted_dist * cos(angle_from distorted ray to middle_ray) because: cos(b) = correct_dist/distorted_dist
// (30 degrees for the leftmost ray and -30 degrees for the right most ray)


// walls are 90° angle to the floor
// cube size =  32*32*32 (in ex 64*64*64 is used)(for now) good with a number divided by 2; because we can perform some arithmetic shift operations on such number (shift operations are faster than multiplication or division).
// player_fov = 60° 
// player_height = cube-unit / 2 = 16 units
//

/*
projection plan: 
distance from player to projection plan = (projectionplan width / 2) / tan(30 (half of fov)) --> 692
angle between rays = fov / projectionplan width (these are columns on the projection plan) 
projected wall slice height = actual wall slice height / dist to the actual wall * dist f. player to projection plane
projected wall slice height = 32 / correct_dist * dist f. player to projection plane
draw vertical line on the corresponding column on projection plane
*/

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
		// printf("cub win width %i\n", cub->win_width);
		while (y < cub->win_height / 2)
		{
			mlx_put_pixel(cub->img, x, y, cub->wall_color);
			y++;
		}
		// Render the floor (bottom half of the screen)
		y = cub->win_height / 2;
		while (y < cub->win_height)
		{
			mlx_put_pixel(cub->img, x, y, cub->floor_color);
			y++;
		}
		x++;
	}
}

mlx_texture_t *wall_texture_direction(t_cub *cub, t_wall_direction *wall_direction)
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

void	render_wallslice(t_cub *cub, t_raycasting *rc)
{
	int				start_y;
	int				end_y;
	int				y;
	int				color;
	mlx_texture_t	*texture;

	texture = wall_texture_direction(cub, &rc->wall_direction);
	rc->line_height = (TILE_SIZE / rc->correct_dist) * cub->dist_pplane;
	if (rc->line_height > cub->win_height)
		rc->line_height = cub->win_height;
	start_y = (cub->win_height / 2) - ((int)rc->line_height / 2);
	end_y = start_y + (int)rc->line_height;
	if (start_y < 0)
		start_y = 0;
	if (end_y > cub->win_height)
		end_y = cub->win_height;
	rc->text_x = (int)(rc->wall_hit_position * texture->width) % texture->width;
	y = start_y;
	while (y < end_y)
	{
		rc->text_y = ((y - start_y) * texture->height) / (int)rc->line_height;
		color = get_texture_color(cub, texture, rc);
		mlx_put_pixel(cub->img, rc->x, y, color);
		y++;
	}
}

//Check this function again to understand
// int get_texture_color(t_cub *cub, mlx_texture_t *texture, t_raycasting *rc)
// {
//     uint32_t *pixels;
// 	uint32_t argb_color;
// 	uint8_t		alpha;
// 	uint8_t		red;
// 	uint8_t		green;
// 	uint8_t		blue;

//     // Bounds check (clamping to texture dimensions)
//     if (rc->text_x < 0)
// 		rc->text_x = 0;
//     if (rc->text_x >= (int)texture->width)
// 		rc->text_x = texture->width - 1;
//     if (rc->text_y < 0)
// 		rc->text_y = 0;
//     if (rc->text_y >= (int)texture->height)
// 		rc->text_y = texture->height - 1;
// 	pixels = wall_text_dir_pixels(cub, rc->wall_direction);
// 	// Extract RGBA components
// 	argb_color = pixels[rc->text_y * texture->width + rc->text_x];
// 	//Convert to RGBA color
// 	red = (argb_color >> 0) & 0xFF;    // Blue channel
// 	blue = (argb_color >> 16) & 0xFF; // Red channel
// 	green = (argb_color >> 8) & 0xFF; // Green channel
// 	alpha = (argb_color >> 24) & 0xFF; // Alpha channel
// 	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
// }

/*
OPTIMIZATON
Use a Profiler:

    Run your program with a profiler (e.g., gprof or valgrind) to pinpoint slow functions and memory issues.

Memory Leaks:

    Use tools like valgrind to detect and fix memory leaks. Ensure all resources (textures, map data) are freed properly.

Reduce Redundant Computations:

    Cache results of expensive operations (e.g., map data, trigonometric calculations).

Parallel Processing:

    Consider using multithreading for rendering or raycasting to utilize multiple CPU cores.

Optimize Rendering:

    Only redraw parts of the screen that have changed (dirty rectangles).

Simplify Loops:

    Analyze nested loops in rendering and raycasting functions for redundant computations.
memory leak doesnt get bigger with longer run time

./cub3d map.cub
gprof ./cub3d gmon.out > analysis.txt
less analysis.txt 
*/