/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/05 17:28:02 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef  struct  s_line
{
	int  x; //the x coordinate of line relative to screen
	int  y; //the current pixel index of the line (along y axis)
	int  y0; //y start index of drawing texture
	int  y1; //y end index of drawing texture
	int  tex_x; //x coordinate of texture to draw
	int  tex_y; //y coordinate of texture to draw
} t_line;

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



// int	get_texture_color(xpm_t *xpm, int text_x, int text_y)
// {

// }


void	render_wallslice(t_cub *cub, float dist, int x)
{
	float	line_height;
    int		start_y;
    int		end_y;
	int		y;
	int		text_x;
	int		text_y;
	// int		color;

	line_height = (TILE_SIZE / dist) * cub->dist_pplane;
	if (line_height > WIN_HEIGHT)
		line_height = WIN_HEIGHT;
    start_y = (WIN_HEIGHT / 2) - ((int)line_height / 2);
    end_y = start_y + (int)line_height;
    if (start_y < 0)
		start_y = 0;
    if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	text_x = (x % TILE_SIZE);
	y = start_y;
    while (y < end_y)
	{
		text_y = ((y - start_y) * TILE_SIZE) / line_height;
		// color = get_texture_color(cub->xpm, text_x, text_y);
        mlx_put_pixel(cub->img, x, y, BLACK);
		y++;
	}
	//closer to the wall --> bigger number
	// printf("height %f\n", line_height);
}

// void render_wallslice(t_cub *cub, float dist, float angle, int x)
// {
//     float line_height;
//     int start_y;
//     int end_y;
//     int color = 0xFFFFFF; // Set this to your wall color or texture

//     // Calculate the projected wall slice height using the distance to the wall and distance to the projection plane
//     line_height = (TILE_SIZE / dist) * cub->dist_pplane;

//     // Limit the line height to the window height (to avoid rendering off-screen)
//     if (line_height > WIN_HEIGHT)
//         line_height = WIN_HEIGHT;

//     // Calculate the vertical position (y-coordinates) on the screen to render the slice
//     start_y = (WIN_HEIGHT / 2) - ((int)line_height / 2);
//     end_y = start_y + (int)line_height;

//     // Ensure the coordinates are within screen bounds
//     if (start_y < 0) start_y = 0;
//     if (end_y > WIN_HEIGHT) end_y = WIN_HEIGHT;

//     // Render the wall slice as a vertical line on the screen
//     for (int y = start_y; y < end_y; y++) {
//         put_pixel(cub->screen, x, y, color); // Replace `put_pixel` with your specific drawing function
//     }
// }


void	render_3D(t_cub *cub)
{
	(void) cub;
}
