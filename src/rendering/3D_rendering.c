/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/10 18:44:59 by eeklund       ########   odam.nl         */
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

	render_floor_ceiling(cub);
	div = -M_PI / 6;
	step = (M_PI / 3) / WIN_WIDTH;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_angle = player->angle + div;
		normalize_angle(&(ray_angle)); // Ensure the angle is within -2PI to 2*PI
		distorted_distance = cast_single_ray(cub, player, ray_angle);
		correct_dist = distorted_distance * cos(div);
		// printf("slice %f\n", round((div + M_PI / 6) / step));
		render_wallslice(cub, correct_dist, x);
		div += step;
		x++;
	}
}

void	render_floor_ceiling(t_cub *cub)
{
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
}

void	render_wallslice(t_cub *cub, float dist, int x)
{
	float	line_height;
    int		start_y;
    int		end_y;
	int		y;
	int		text_x;
	int		text_y;
	int		color;

	// Calculate the projected wall slice height using the distance to the wall and distance to the projection plane
	line_height = (TILE_SIZE / dist) * cub->dist_pplane;
	if (line_height > WIN_HEIGHT) //make sure its not rendering off screen
		line_height = WIN_HEIGHT;
	// Calculate the vertical position (y-coordinates) on the screen to render the slice
    start_y = (WIN_HEIGHT / 2) - ((int)line_height / 2);
    end_y = start_y + (int)line_height;
	// Ensure the coordinates are within screen bounds
    if (start_y < 0)
		start_y = 0;
    if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	text_x = (x % TILE_SIZE);
	y = start_y;
	// Render the wall slice as a vertical line on the screen
    while (y < end_y)
	{
		text_y = ((y - start_y) * TILE_SIZE) / (int)line_height;
		color = get_texture_color(cub, text_x, text_y);
		// printf("color is %i\n", color);
        mlx_put_pixel(cub->img, x, y, color);
		y++;
	}
	//closer to the wall --> bigger number
	// printf("height %f\n", line_height);
}


int get_texture_color(t_cub *cub, int text_x, int text_y)
{
    uint32_t *pixels;

    // Bounds check
    if (text_x < 0 || text_x >= (int)cub->text->no->width || text_y < 0 || text_y >= (int)cub->text->no->height)
        return 0; // Default to black if out of bounds

    pixels = (uint32_t *)cub->text->no_img->pixels;

    // Extract alpha, red, green, blue components
    unsigned char alpha = (pixels[text_y * cub->text->no->width + text_x] & 0xFF000000) >> 24;
    unsigned char red = (pixels[text_y * cub->text->no->width + text_x] & 0x00FF0000) >> 16;
    unsigned char green = (pixels[text_y * cub->text->no->width + text_x] & 0x0000FF00) >> 8; // look at it tomorrow I dont know what the fuck is going on
    unsigned char blue = pixels[text_y * cub->text->no->width + text_x] & 0x000000FF;

    // Recombine into MLX42 format
    unsigned int mlx42_color = (alpha << 24) | (red << 16) | (green << 8) | blue;

    return mlx42_color;
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