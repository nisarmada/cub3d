/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:45:46 by nikos         #+#    #+#                 */
/*   Updated: 2024/11/26 15:03:24 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_player *player, char direction)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	// printf("Before move - x: %f, y: %f, angle: %f\n", player->x, player->y, player->angle);
	if (direction == 'W')
	{
		move_x = cos(player->angle) * MOVE_SPEED;
		move_y = -sin(player->angle) * MOVE_SPEED;
		// printf("Moving forward - move_x: %f, move_y: %f\n", move_x, move_y);
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
		player->angle += ROTATION_SPEED;
	if (direction == 'R')
		player->angle -= ROTATION_SPEED;
	normalize_angle(&(player->angle));
}

void key_hook(mlx_key_data_t keycode, void *cub_ptr)
{
	t_cub *cub;

	cub = (t_cub *)cub_ptr;
	if (keycode.action == MLX_PRESS)
		cub->keys[keycode.key] = true;
	else if (keycode.action == MLX_RELEASE)
		cub->keys[keycode.key] = false;
	if (keycode.key == MLX_KEY_ESCAPE && keycode.action == MLX_RELEASE)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
	// if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS)
	// 	move_player(cub->player, 'W');
	// if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS)
	// 	move_player(cub->player, 'S');
	// if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS)
	// 	rotate_player(cub->player, 'L');
	// if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS)
	// 	rotate_player(cub->player, 'R');
	// render_map(cub->img, cub);
	// render_player(cub, cub->img);
	// return 1;
}

void hook_loop(void *cub_ptr)
{
	t_cub *cub;

	cub = (t_cub *)cub_ptr;
	if (cub->keys[MLX_KEY_W])
		move_player(cub->player, 'W');
	if (cub->keys[MLX_KEY_S])
		move_player(cub->player, 'S');
	if (cub->keys[MLX_KEY_A])
		rotate_player(cub->player, 'L');
	if (cub->keys[MLX_KEY_D])
		rotate_player(cub->player, 'R');
	render_map(cub->img, cub);
	render_player(cub, cub->img);
}