/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 15:08:54 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/15 15:39:09 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (line[0] == '1' || line[0] == '0')
			break;
		line = get_next_line(fd);
	}
	while (line)
	{
		line = get_next_line(fd);
		rows++;
	}
	//printf("this many rows %i\n", rows);
	cub->map = malloc(sizeof(char *) * rows);
	close(fd);
}

void map_parsing(char *line, t_cub *cub, int j)
{
	int i;

	i = 0;
	(void)j;
	while (line[i])
	{
		// if (line[i] == 'N')
		// 	player_position(line, cub);
		i++;
	}
	cub->map[j] = ft_strdup(line);
	if (!cub->map_width || i > cub->map_width)
		cub->map_width = i;
}