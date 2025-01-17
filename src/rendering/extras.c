/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extras.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:59:53 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/19 19:55:55 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

void draw_line(t_cub *cub, int x, int y, float scale)
{
	t_line	line;

	init_line_1(&line, cub, scale);
	init_line_2(&line, x, y);
	init_line_direction(&line);
	while (1)
	{
		draw_line_pixel(&line, cub);
		if (line.x0 == x && line.y0 == y)
			break ;
		update_line_position(&line);
	}
}

static uint32_t	*wall_text_dir_pixels(t_cub *cub,
	t_wall_direction wall_direction)
{
	if (wall_direction == NORTH)
		return ((uint32_t *)cub->text->no_img->pixels);
	else if (wall_direction == SOUTH)
		return ((uint32_t *)cub->text->so_img->pixels);
	else if (wall_direction == EAST)
		return ((uint32_t *)cub->text->ea_img->pixels);
	else
		return ((uint32_t *)cub->text->we_img->pixels);
}

int	get_texture_color(t_cub *cub, mlx_texture_t *texture, t_raycasting *rc)
{
	uint32_t	*pixels;
	uint32_t	argb_color;
	t_rgb		color;

    // Bounds check (clamping to texture dimensions)
	if (rc->text_x < 0)
		rc->text_x = 0;
	if (rc->text_x >= (int)texture->width)
		rc->text_x = texture->width - 1;
	if (rc->text_y < 0)
		rc->text_y = 0;
	if (rc->text_y >= (int)texture->height)
		rc->text_y = texture->height - 1;
	pixels = wall_text_dir_pixels(cub, rc->wall_direction);
	// Extract RGBA components
	argb_color = pixels[rc->text_y * texture->width + rc->text_x];
	//Convert to RGBA color
	color.red = (argb_color >> 0) & 0xFF;    // Blue channel
	color.blue = (argb_color >> 16) & 0xFF; // Red channel
	color.green = (argb_color >> 8) & 0xFF; // Green channel
	color.alpha = (argb_color >> 24) & 0xFF; // Alpha channel
	return ((color.red << 24) | (color.green << 16)
		| (color.blue << 8) | color.alpha);
}
