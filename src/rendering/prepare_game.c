/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_game.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 14:14:42 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/21 17:27:33 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_game(t_cub *cub)
{
	void	*mlx;
	// void	*window;
	mlx_image_t *img;

	(void)cub;
	mlx = mlx_init(800, 600, "Cub3d", true);
	if (!mlx)
		return (1);
	img = mlx_new_image(mlx, 800, 600);
	if (!img)
		return (1);
	render_map(img, cub);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

void draw_tile(mlx_image_t *img, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(img, x + i, j + y, color);
			j++;
		}
		i++;
	}
}

void render_map(mlx_image_t *img, t_cub *cub)
{
	int row;
	int column;
	int	tile_x;
	int	tile_y;

	row = 0;
	//printf("wall color %i\n", cub->wall_color);
	while (cub->map[row])
	{
		column = 0;
		while (cub->map[row][column])
		{
			tile_x = TILE_SIZE * column;
			tile_y = TILE_SIZE * row;
			if (cub->map[row][column] == '1') //wall
				draw_tile(img, tile_x, tile_y, WALL_COLOR);
			else if (cub->map[row][column] == '0')
				draw_tile(img, tile_x, tile_y, FLOOR_COLOR);
			else if (cub->map[row][column] == ' ')
				draw_tile(img, tile_x, tile_y, INACCESSIBLE_COLOR);
			else if (cub->map[row][column] == 'N' || cub->map[row][column] == 'S' || 
                     cub->map[row][column] == 'E' || cub->map[row][column] == 'W')
			{
				draw_tile(img, tile_x, tile_y, FLOOR_COLOR);
				cub->player->x = column * TILE_SIZE + TILE_SIZE / 2;
				cub->player->y = row * TILE_SIZE + TILE_SIZE / 2;
			}
			column++;
		}
		row++;
	}
}

