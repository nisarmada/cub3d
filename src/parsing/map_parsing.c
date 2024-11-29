/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 15:08:54 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/29 15:03:10 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' \
	|| c == 'W' || c == 'E' || c == ' ');
}

int is_map_line(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
        return (0);
	while (line[i])
	{
		if (!is_map_char(line[i]) && line[i] != '\n')
			{
				//printf("line[%i] %c\n", i, line[i]);
				return (0);
			}
		i++;
	}
	return (1);
}
void	allocate_map(char *filename, t_cub *cub)
{
	int fd;
	char	*line;
	int		rows;

	fd = open(filename, O_RDONLY);
	rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			break;
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!cub->map_width || ft_strlen(line) - 1 > (size_t)cub->map_width)
			cub->map_width = ft_strlen(line) - 1;
		line = get_next_line(fd);
		rows++;
	}
	// printf("this many rows %i\n", rows);
	cub->map_height = rows - 1;
	// printf("map height: %i\n", cub->map_height);
	// printf("map width: %i\n", cub->map_width);
	cub->map = malloc(sizeof(char *) * (rows + 1));
	close(fd);
}

void map_parsing(char *line, t_cub *cub, int j)
{
	int i;
	//char *final_line;

	i = 0;
	(void)j;
	cub->map[j] = malloc(sizeof(char) * cub->map_width + 1);
	if (!cub->map[j])
	return ;
	while (i < (int)(ft_strlen(line) - 1))
	{
		cub->map[j][i] = line[i];
		i++;
	}
	while (i < cub->map_width)
	{
		cub->map[j][i] = ' ';
		i++;
	}
	cub->map[j][i] = '\0';
	// print_map(cub);
}

int	valid_first_last_row(char **map, int row, int width)
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

int	check_surrounding(char **map, int row, int i, int width)
{
	char	*cur; 
	char	*up;
	char	*down;

	cur = map[row];
	up = map[row - 1];
	down = map[row + 1];
	if (i != 0 && (cur[i - 1] != '1' && cur[i - 1] != ' '))
		return (0);
	if (i != width && (cur[i + 1] != '1'  && cur[i + 1] != ' '))
		return (0);
	if ((up[i] != '1' && up[i] != ' ') || (down[i] != '1'))
		return (0);
	return (1);
}

int	check_char(t_cub *cub, int row, int i)
{
	if (i == 0 && cub->map[row][i] != '1')
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
		return (printf("wrong first or last line\n"), 0); //errr func with nice error msgs
	row = 1;
	while (row < height - 1)
	{
		i = 0;
		while (i < width)
		{
			if (map[row][i] == ' ')
			{
				if (!check_surrounding(map, row, i, cub->map_width - 1))
					return (printf("leak in map, row: %i, index: %i\n", row, i), 0);
			}
			else
			{
				if (!check_char(cub, row, i))
					return (printf("invalid char %i %i\n", row, i), 0);
			}
			i++;
		}
		row++;
	}
	if (!cub->player->orientation)
		return(printf("no player\n"), 0);	
	printf("map checked ;)\n");
	return (1);
}