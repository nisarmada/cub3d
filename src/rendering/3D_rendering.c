/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/13 17:13:02 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef  struct  s_slice
{
	int  x; //the x coordinate of line relative to screen
	int  y; //the current pixel index of the line (along y axis)
	int  start_y; //y start index of drawing texture
	int  end_y; //y end index of drawing texture
	int  text_x; //x coordinate of texture to draw
	int  text_y; //y coordinate of texture to draw
} t_slice;

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

void render_3D_view(t_cub *cub, t_player *player)
{
	float	distorted_distance;
	float	correct_dist;
	float	div;
	float	ray_angle;
	float	step;
	int		x;
	float	wall_hit_position;
	t_wall_direction	wall_direction;

	// printf("hello\n");
	render_floor_ceiling(cub);
	div = -M_PI / 6;
	step = (M_PI / 3) / cub->win_width;
	x = 0;
	while (x < cub->win_width)
	{
		ray_angle = player->angle + div;
		normalize_angle(&(ray_angle)); // Ensure the angle is within -2PI to 2*PI
		distorted_distance = cast_single_ray(cub, ray_angle, &wall_hit_position, &wall_direction);
		correct_dist = distorted_distance * cos(div);
		// printf("slice %f\n", round((div + M_PI / 6) / step));
		render_wallslice(cub, correct_dist, x, wall_hit_position, wall_direction);
		div += step;
		x++;
	}
}

void	render_floor_ceiling(t_cub *cub)
{
	int		x;
	int		y;

	x = 0;
	while (x < cub->win_width) 
	{
		// Render the ceiling (top half of the screen)
		y = 0;
		while (y < WIN_HEIGHT / 2) {
			mlx_put_pixel(cub->img, x, y, cub->wall_color);
			y++;
		}
		// Render the floor (bottom half of the screen)
		y = WIN_HEIGHT / 2;
		while (y < WIN_HEIGHT) {
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

static uint32_t *wall_texture_direction_pixels(t_cub *cub, t_wall_direction wall_direction)
{
	if (wall_direction == NORTH)
		return ((uint32_t *)cub->text->no_img);
	else if (wall_direction == SOUTH)
		return ((uint32_t *)cub->text->so_img);
	else if (wall_direction == EAST)
		return ((uint32_t *)cub->text->ea_img);
	else if (wall_direction == WEST)
		return ((uint32_t *)cub->text->we_img);
	return ((uint32_t *)cub->text->no_img);
}

void	render_wallslice(t_cub *cub, float dist, int x, float wall_hit_position, t_wall_direction wall_direction)
{
	float	line_height;
    int		start_y;
    int		end_y;
	int		y;
	int		text_x;
	int		text_y;
	int		color;
	mlx_texture_t *texture;

	texture = wall_texture_direction(cub, &wall_direction);
	// Calculate the projected wall slice height using the distance to the wall and distance to the projection plane
	line_height = (TILE_SIZE / dist) * cub->dist_pplane;
	if (line_height > cub->win_height) //make sure its not rendering off screen
		line_height = cub->win_height;
	// Calculate the vertical position (y-coordinates) on the screen to render the slice
    start_y = (cub->win_height / 2) - ((int)line_height / 2);
    end_y = start_y + (int)line_height;
	// Ensure the coordinates are within screen bounds
    if (start_y < 0)
		start_y = 0;
    if (end_y > cub->win_height)
		end_y = cub->win_height;
	text_x = (x % TILE_SIZE);
	text_x = (int)(wall_hit_position * texture->width) % texture->width;
	y = start_y;
	// Render the wall slice as a vertical line on the screen
    while (y < end_y)
	{
		text_y = ((y - start_y) * texture->height) / (int)line_height;
		color = get_texture_color(cub, text_x, text_y, texture, wall_direction);
		// printf("color is %i\n", color);
        mlx_put_pixel(cub->img, x, y, color);
		y++;
	}
	//closer to the wall --> bigger number
	// printf("height %f\n", line_height);
}

//Check this function again to understand
int get_texture_color(t_cub *cub, int text_x, int text_y, mlx_texture_t *texture, t_wall_direction wall_direction)
{
    uint32_t *pixels;
	uint32_t argb_color;
	uint8_t		alpha;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;

    // Bounds check (clamping to texture dimensions)
    if (text_x < 0)
		text_x = 0;
    if (text_x >= (int)texture->width)
		text_x = texture->width - 1;
    if (text_y < 0)
		text_y = 0;
    if (text_y >= (int)texture->height)
		text_y = texture->height - 1;

	pixels = wall_texture_direction_pixels(cub, wall_direction);
	// Extract RGBA components
	argb_color = pixels[text_y * texture->width + text_x];
	//Convert to RGBA color
	alpha = (argb_color >> 24) & 0xFF;
	// printf("alpha %i\n", alpha);
	red = (argb_color >> 16) & 0xFF;
	green = (argb_color >> 8) & 0xFF;
	blue = argb_color & 0xFF;
    // Return RGBA
    return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

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