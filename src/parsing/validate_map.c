/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 15:36:00 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/27 09:11:06 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_outer_row(char **map, int row, int width)
{
	int	i;

	i = 0;
	while (i < width - 1)
	{
		if (map[row][i] != ' ' && map[row][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	valid_map(t_cub *cub, int height, int width)
{
	int	row;

	if (!valid_outer_row(cub->map, 0, width) || \
	!valid_outer_row(cub->map, height - 1, width))
		return (error_msg("Error\nLeak in map\n", 0));
	row = 1;
	while (row < height - 1)
	{
		if (!valid_map_row(cub, row))
			return (0);
		row++;
	}
	if (!cub->player->orientation)
		return (error_msg("Error\nNo player\n", 0));
	return (1);
}
