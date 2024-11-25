/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:45:46 by nikos         #+#    #+#                 */
/*   Updated: 2024/11/25 19:10:05 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_player *player, char direction)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
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
	player->x += move_x;
	player->y += move_y;
}

void rotate_player(t_player *player, char direction)
{
	if (direction == 'L')
		player->angle -= ROTATION_SPEED;
	if (direction == 'R')
		player->angle += ROTATION_SPEED;
	normalize_angle(&(player->angle));
}

void key_hook(mlx_key_data_t keycode, void *cub_ptr)
{
	t_cub *cub;

	cub = (t_cub *)cub_ptr;
	printf("Keycode: %d\n", keycode.key);
	if (keycode.key == MLX_KEY_ESCAPE && keycode.action == MLX_RELEASE)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
	// return 1;
}