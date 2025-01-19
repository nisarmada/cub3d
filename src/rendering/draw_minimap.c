/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 18:41:18 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/19 20:26:42 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(mlx_image_t *img, t_coord *tile, float scale, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (TILE_SIZE * scale))
	{
		j = 0;
		while (j < (TILE_SIZE * scale))
		{
			mlx_put_pixel(img, tile->x + i, j + tile->y, color);
			j++;
		}
		i++;
	}
}

int	determine_tile_color(char tile)
{
	if (tile == '1')
		return (WALL_COLOR);
	else if (tile == '0')
		return (FLOOR_COLOR);
	else if (tile == ' ')
		return (INACCESSIBLE_COLOR);
	else if (!ft_strchr("NSWE", tile))
		return (FLOOR_COLOR);
	return (FLOOR_COLOR);
}

typedef struct s_render_context
{
	float		scale;
	mlx_image_t	*img;
}	t_render_context;

void	render_map_tile(int row, int col, t_cub *cub, t_render_context *context)
{
	t_coord	tile;
	int		color;

	tile.x = col * TILE_SIZE * context->scale;
	tile.y = row * TILE_SIZE * context->scale;
	color = determine_tile_color(cub->map[row][col]);
	draw_tile(context->img, &tile, context->scale, color);
}

void	render_map_grid(t_render_context *context, t_cub *cub)
{
	int	row;
	int	column;

	row = 0;
	while (row < cub->map_height)
	{
		column = 0;
		while (column < cub->map_width)
		{
			render_map_tile(row, column, cub, context);
			column++;
		}
		row++;
	}
}

float	render_map(mlx_image_t *img, t_cub *cub)
{
	t_render_context	context;

	context.img = img;
	context.scale = calculate_scale(cub->map_width, cub->map_height);
	render_map_grid(&context, cub);
	render_fov(cub->player, cub, context.scale);
	return (context.scale);
}
