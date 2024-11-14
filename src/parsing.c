/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/14 16:41:21 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cub *initialize_cub(void)
{
	t_cub *cub;

	cub = malloc(sizeof(t_cub));
	cub->east = NULL;
	cub->west = NULL;
	cub->north = NULL;
	cub->south = NULL;
	cub->map = NULL;
	return (cub);
}

void parse_cub_file(char *filename, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	// parse_directions(line, cub);
	line = get_next_line(fd);
	while (line)
	{
		printf("line is %s\n", line);
		line = get_next_line(fd);
	}
}