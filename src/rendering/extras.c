/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extras.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:59:53 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/19 19:19:37 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

// void normalize_angle(float *angle)
// {
//     while (*angle < 0)
//         *angle += 2 * M_PI;
//     while (*angle > 2 * M_PI)
//         *angle -= 2 * M_PI;
// }


void	draw_line(t_cub *cub, int x, int y, float scale)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	x0;
	int	y0;
	int	err;
	int	err2;

	x0 = cub->player->x * scale;
	y0 = cub->player->y * scale;
	dx = abs(x - x0); // x1 - x0
	dy = abs(y - y0); // y1 - y0
	err = dx - dy;
	if (x > x0)
		sx = 1;
	else
		sx = -1;
	if (y > y0)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		if (x0 >= 0 && x0 < cub->win_width && y0 >= 0 && y0 < cub->win_height)
			mlx_put_pixel(cub->img, x0, y0, GREEN);
		if (x0 == x && y0 == y)
			break ;
		err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
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
