/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:45:46 by nikos         #+#    #+#                 */
/*   Updated: 2024/11/25 13:59:26 by nikos         ########   odam.nl         */
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

int key_hook(int keycode, t_cub *cub)
{
	(void)cub;
	printf("Keycode: %d\n", keycode);
	return 1;
}