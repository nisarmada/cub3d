/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_miniplayer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 20:11:20 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/24 16:00:32 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

float	calculate_scale(int map_width, int map_height, mlx_image_t *img)
{
	t_coord	scale_coord;
	float	scale;
	float	minimap_scale;

	minimap_scale = 0.28f;
	scale_coord.x = (float)img->width * minimap_scale / (map_width * TILE_SIZE);
	scale_coord.y = (float)img->height * minimap_scale
		/ (map_height * TILE_SIZE);
	scale = fminf(scale_coord.x, scale_coord.y);
	return (scale);
}

void	render_player(t_cub *cub, mlx_image_t *img, float scale)
{
	int	x;
	int	y;
	int	r;
	int	i;
	int	j;

	x = cub->player->x * scale;
	y = cub->player->y * scale;
	r = (TILE_SIZE * scale) / 2;
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
			{
				mlx_put_pixel(img, x + i, y + j, GREEN);
			}
			j++;
		}
		i++;
	}
}
