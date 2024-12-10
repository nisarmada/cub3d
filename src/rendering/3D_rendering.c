/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/10 18:28:08 by nsarmada      ########   odam.nl         */
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
	int		color;

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
	// printf("HHELLOchfdfgdrs\n");
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


void	render_3D(t_cub *cub)
{
	(void) cub;
}
