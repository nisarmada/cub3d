/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:45:46 by nikos         #+#    #+#                 */
/*   Updated: 2024/12/12 14:44:04 by eeklund       ########   odam.nl         */
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
	new_x = player->x + move_x;
	new_y = player->y + move_y;
	x_tile = new_x / TILE_SIZE; // Convert new position to tile coordinates
	player->changed = 1;
	y_tile = new_y / TILE_SIZE;
	if (cub->map[y_tile][x_tile] != '1') // if there's no wall in x axis update x-coordinate
        player->x = new_x;
    if (cub->map[y_tile][x_tile] != '1') // if there's no wall in y axis update y-coordinate
        player->y = new_y;
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
		free_and_exit_game(cub, EXIT_SUCCESS);
}

void hook_loop(void *cub_ptr)
{
	t_cub *cub;

	cub = (t_cub *)cub_ptr;
	if (cub->keys[MLX_KEY_W])
		move_player(cub, cub->player, 'W');
	if (cub->keys[MLX_KEY_S])
		move_player(cub, cub->player, 'S');
	if (cub->keys[MLX_KEY_A])
		rotate_player(cub->player, 'L');
	if (cub->keys[MLX_KEY_D])
		rotate_player(cub->player, 'R');
	if (cub->player->changed == 1)
	{
		render_frame(cub);
		cub->player->changed = 0;
	}
}