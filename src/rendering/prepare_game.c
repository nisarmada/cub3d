/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_game.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 14:14:42 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/02 12:47:36 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_game(t_cub *cub)
{
	//void	*mlx;
	//mlx_image_t *img;

	(void)cub;
	cub->mlx = mlx_init(900, 800, "Cub3d", true);
	if (!cub->mlx)
		return (1);
	cub->img = mlx_new_image(cub->mlx, 1000, 800);
	if (!cub->img)
		return (1);
	render_map(cub->img, cub);
	render_player(cub, cub->img);
	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_loop_hook(cub->mlx, hook_loop, cub);
	// raycasting(cub, cub->player);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_loop(cub->mlx);
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
	while (cub->map[row])
	{
		column = 0;
		while (column < cub->map_width)
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
				draw_tile(img, tile_x, tile_y, FLOOR_COLOR);
				
			column++;
		}
		row++;
	}
	render_fov(cub->player, img, cub);
	raycasting(cub, cub->player);
}

void render_player(t_cub *cub, mlx_image_t *img)
{
	int x;
	int y;
	int r;
	int i;
	int j;

	x = cub->player->x;
	y = cub->player->y;
	r = TILE_SIZE / 4;
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
	// render_fov(cub->player, img);
}

void render_fov(t_player *player, mlx_image_t *img, t_cub *cub)
{
	int max_distance;
	float	left_angle;
	float	right_angle;
	int		x_left;
	int		y_left;
	int		x_right;
	int		y_right;
	
	(void)cub;
	max_distance = 400;
	left_angle = player->angle + player->fov / 2;
	right_angle = player->angle - player->fov / 2;
	normalize_angle(&left_angle);
	normalize_angle(&right_angle);
	x_left = player->x + cos(left_angle) * max_distance;
	y_left = player->y - sin(left_angle) * max_distance;
	x_right = player->x + cos(right_angle) * max_distance;
	y_right = player->y - sin(right_angle) * max_distance;
	draw_line(player, img, x_left, y_left);
	draw_line(player, img, x_right, y_right);
	// raycasting(cub, cub->player);
}
