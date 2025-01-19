/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:45:46 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/19 11:45:34 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_cub *cub, t_player *player, char direction)
{
	float	move_x;
	float	move_y;
	int		x_tile;
	int		y_tile;
	float	new_x;
	float	new_y;
	float	padding;
	float	check_x;
	float	check_y;

	move_x = 0;
	move_y = 0;
	new_x = 0;
	new_y = 0;
	if (direction == 'W')
	{
		move_x = cos(player->angle) * MOVE_SPEED;
		move_y = -sin(player->angle) * MOVE_SPEED;
	}
	else if (direction == 'S')
	{
		move_x = -cos(player->angle) * MOVE_SPEED;
		move_y = sin(player->angle) * MOVE_SPEED;
	}
	else if (direction == 'A')
    {
        move_x = sin(player->angle) * MOVE_SPEED;
        move_y = cos(player->angle) * MOVE_SPEED;
    }
	else if (direction == 'D')
    {
        move_x = -sin(player->angle) * MOVE_SPEED;
        move_y = -cos(player->angle) * MOVE_SPEED;
    }
	new_x = player->x + move_x;
	new_y = player->y + move_y;
	// printf("Angle: %f, Direction: %c, Move_X: %f, Move_Y: %f\n", player->angle, direction, move_x, move_y);
	padding = TILE_SIZE * 0.2;
	if (move_x > 0)
    	check_x = new_x + padding;
	else
		check_x = new_x - padding;
	if (move_y > 0)
		check_y = new_y + padding;
	else
		check_y = new_y - padding;
	x_tile = floor(check_x / TILE_SIZE); // Convert new position to tile coordinates
	y_tile = floor(check_y / TILE_SIZE);
	if (cub->map[y_tile][(int)floor(player->x / TILE_SIZE)] != '1')
		player->y = new_y;
	if (cub->map[(int)floor(player->y / TILE_SIZE)][x_tile] != '1')
		player->x = new_x;
	player->changed = 1;
}

void rotate_player(t_player *player, char direction)
{
	if (direction == 'L')
		player->angle -= ROTATION_SPEED;
	if (direction == 'R')
		player->angle += ROTATION_SPEED;
	normalize_angle(&(player->angle));
	player->changed = 1;
}

void key_hook(mlx_key_data_t keycode, void *cub_ptr)
{
	t_cub *cub;
	const int max_keys = sizeof(cub->keys) / sizeof(cub->keys[0]);

	cub = (t_cub *)cub_ptr;
	if (keycode.key >= 0 && keycode.key < max_keys) //no keys out of bounds
	{
		if (keycode.action == MLX_PRESS)
			cub->keys[keycode.key] = true;
		else if (keycode.action == MLX_RELEASE)
			cub->keys[keycode.key] = false;
	}
	if (keycode.key == MLX_KEY_ESCAPE && keycode.action == MLX_RELEASE)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
}

void hook_loop(void *cub_ptr)
{
	t_cub *cub;

	cub = (t_cub *)cub_ptr;
	// printf("key is %i\n", )
	if (cub->keys[MLX_KEY_W])
		move_player(cub, cub->player, 'W');
	if (cub->keys[MLX_KEY_S])
		move_player(cub, cub->player, 'S');
	if (cub->keys[MLX_KEY_A])
		move_player(cub, cub->player, 'A');
	if (cub->keys[MLX_KEY_D])
		move_player(cub, cub->player, 'D');	
	if (cub->keys[MLX_KEY_LEFT])
		rotate_player(cub->player, 'L');
	if (cub->keys[MLX_KEY_RIGHT])
		rotate_player(cub->player, 'R');
	if (cub->player->changed == 1)
	{
		render_frame(cub);
		cub->player->changed = 0;
	}
}

void	resize_callback(int32_t width, int32_t height, void* param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->img)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = NULL;
	}
	if (width < 200)
		width = 200;
	if (height < 200)
		height = 200;
	cub->win_width = width;
	cub->win_height = height;
	cub->img = mlx_new_image(cub->mlx, cub->win_width, cub->win_height);
	if (!cub->img)
		free_and_exit_game(cub, EXIT_FAILURE);
	cub->dist_pplane = ((cub->win_width / 2 ) / tan(0.524));
    if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0)
        free_and_exit_game(cub, EXIT_FAILURE);
	ft_memset(cub->img->pixels, 0, cub->img->width * cub->img->height * sizeof(int32_t));
	// render_floor_ceiling(cub);
	render_3D_view(cub, cub->player);
	float scale = render_map(cub->img, cub);
	render_player(cub, cub->img, scale);
}
