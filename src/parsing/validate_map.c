/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 15:36:00 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/30 13:25:37 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_outer_row(t_cub *cub, int row, int width)
{
	int		i;
	char	**map;

	i = 0;
	map = cub->map;
	while (i < width - 1)
	{
		if (map[row][i] != ' ' && map[row][i] != '1')
			return (0);
		if (map[row][i] == ' ')
		{
			if (!check_surrounding(map, row, i, cub))
				return (0);
		}
		i++;
	}
	return (1);
}

int	valid_map(t_cub *cub, int height, int width)
{
	int	row;

	if (!valid_outer_row(cub, 0, width) || \
	!valid_outer_row(cub, height - 1, width))
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
