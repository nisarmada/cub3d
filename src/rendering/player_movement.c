/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 13:45:46 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/22 12:09:56 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"


void	movement(char direction, float player_angle, t_coord *move)
{
	if (direction == 'W')
	{
		move->x = cos(player_angle) * MOVE_SPEED;
		move->y = -sin(player_angle) * MOVE_SPEED;
	}
	else if (direction == 'S')
	{
		move->x = -cos(player_angle) * MOVE_SPEED;
		move->y = sin(player_angle) * MOVE_SPEED;
	}
	else if (direction == 'A')
	{
		move->x = sin(player_angle) * MOVE_SPEED;
		move->y = cos(player_angle) * MOVE_SPEED;
	}
	else if (direction == 'D')
	{
		move->x = -sin(player_angle) * MOVE_SPEED;
		move->y = -cos(player_angle) * MOVE_SPEED;
	}
}

void	get_check_pos(float new_x, float new_y, t_coord *move, t_coord *check)
{
	float	padding;

	padding = TILE_SIZE * 0.2;
	if (move->x > 0)
		check->x = new_x + padding;
	else
		check->x = new_x - padding;
	if (move->y > 0)
		check->y = new_y + padding;
	else
		check->y = new_y - padding;
}

void	move_player(t_cub *cub, t_player *player, char direction)
{
	t_coord		move;
	t_coord		check;
	t_coord		new;
	int			x_tile;
	int			y_tile;

	movement(direction, player->angle, &move);
	new.x = player->x + move.x;
	new.y = player->y + move.y;
	get_check_pos(new.x, new.y, &move, &check);
	x_tile = floor(check.x / TILE_SIZE);
	y_tile = floor(check.y / TILE_SIZE);
	if (cub->map[y_tile][(int)floor(player->x / TILE_SIZE)] != '1')
		player->y = new.y;
	if (cub->map[(int)floor(player->y / TILE_SIZE)][x_tile] != '1')
		player->x = new.x;
	player->changed = 1;
}

void	rotate_player(t_player *player, char direction)
{
	if (direction == 'L')
		player->angle -= ROTATION_SPEED;
	if (direction == 'R')
		player->angle += ROTATION_SPEED;
	normalize_angle(&(player->angle));
	player->changed = 1;
}
