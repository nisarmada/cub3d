/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_row.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 15:18:05 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/29 17:44:32 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_surrounding(char **map, int row, int i, int width)
{
	char	*cur;
	char	*up;
	char	*down;

	cur = map[row];
	up = map[row - 1];
	down = map[row + 1];
	if (i == width && cur[i] == '0')
		return (0);
	if (i != 0 && (cur[i - 1] != '1' && cur[i - 1] != ' '))
		return (0);
	if (i != width && (cur[i + 1] != '1' && cur[i + 1] != ' '))
		return (0);
	if ((up && up[i] != '1' && up[i] != ' ')) //could still segfault?
	{
		return (0);
	}
	if (down && down[i] != '1' && down[i] != ' ') //could still segfault? if no down[i]
		return (0);
	return (1);
}

static void	define_field_of_vision(t_cub *cub)
{
	cub->player->fov = M_PI / 3;
	if (cub->player->orientation == 'E')
		cub->player->angle = 0;
	else if (cub->player->orientation == 'N')
		cub->player->angle = M_PI / 2;
	else if (cub->player->orientation == 'S')
		cub->player->angle = 3 * M_PI / 2;
	else if (cub->player->orientation == 'W')
		cub->player->angle = M_PI;
}

static int	check_char(t_cub *cub, int row, int i)
{
	if ((i == 0 && cub->map[row][i] != '1'))
		return (error_msg("wrong, \n", 0));
	if (!ft_strchr("NSEW01", cub->map[row][i]))
		return (error_msg("Error\nInvalid char\n", 0));
	if (!cub->player->orientation && ft_strchr("NSEW", cub->map[row][i]))
	{
		cub->player->orientation = cub->map[row][i];
		cub->player->y = row * TILE_SIZE + TILE_SIZE / 2;
		cub->player->x = i * TILE_SIZE + TILE_SIZE / 2;
		define_field_of_vision(cub);
	}
	else if (cub->player->orientation && ft_strchr("NSEW", cub->map[row][i]))
		return (error_msg("Error\nPlayer alredy exists\n", 0));
	return (1);
}

int	valid_map_row(t_cub	*cub, int row)
{
	int	i;

	i = 0;
	while (i < cub->map_width)
	{
		if (cub->map[row][i] == ' ')
		{
			if (!check_surrounding(cub->map, row, i, cub->map_width - 1))
				return (error_msg("Error\nLeak in map\n", 0));
		}
		else
		{
			if (!check_char(cub, row, i))
				return (0);
		}
		i++;
	}
	return (1);
}
