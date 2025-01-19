/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 15:36:00 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 17:12:12 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_first_last_row(char **map, int row, int width)
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

static int	check_surrounding(char **map, int row, int i, int width)
{
	char	*cur;
	char	*up;
	char	*down;

	cur = map[row];
	up = map[row - 1];
	down = map[row + 1];
	if (i == width && cur[i] == '0') // maybe fixed the small error of having last one a 0 but in line with the 1s with this
		return (0);
	if (i != 0 && (cur[i - 1] != '1' && cur[i - 1] != ' '))
		return (0);
	if (i != width && (cur[i + 1] != '1' && cur[i + 1] != ' '))
		return (0);
	if ((up[i] != '1' && up[i] != ' '))
		return (0);
	if (down[i] != '1' && (down[i] != ' '))
		return (0);
	return (1);
}

static void	define_field_of_vision(t_cub *cub)
{
	cub->player->fov = M_PI / 3; //60o
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
		return (printf("wrong, \n"), 0);
	if (!ft_strchr("NSEW01", cub->map[row][i]))
		return (printf("invalid char: %c\n", cub->map[row][i]), 0);
	if (!cub->player->orientation && ft_strchr("NSEW", cub->map[row][i]))
	{
		cub->player->orientation = cub->map[row][i];
		cub->player->y = row * TILE_SIZE + TILE_SIZE / 2;
		cub->player->x = i * TILE_SIZE + TILE_SIZE / 2;
		define_field_of_vision(cub);
	}
	else if (cub->player->orientation && ft_strchr("NSEW", cub->map[row][i]))
		return (printf("player alredy exists, x %i, y %i\n", i, row), 0);
	return (1);
}

int valid_map(t_cub *cub, int height, int width)
{
	int		row;
	int		i;
	char	**map;

	map = cub->map;
	if (!valid_first_last_row(map, 0, width) || \
	!valid_first_last_row(map, height, width))
	{
		return (error_msg("wrong first or last line\n", 0));
	}
	row = 1;
	while (row < height - 1)
	{
		i = 0;
		while (i < width)
		{
			if (map[row][i] == ' ')
			{
				if (!check_surrounding(map, row, i, cub->map_width - 1))
				{
					return (printf("leak in map, row: %i, index: %i\n", row, i), 0);
				}
			}
			else
			{
				if (!check_char(cub, row, i))
				{
					return (printf("invalid char in row:%i index:%i\n", row, i), 0);
				}
			}
			i++;
		}
		row++;
	}
	if (!cub->player->orientation)
		return (error_msg("no player\n", 0));
	return (1);
}
