/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 15:08:10 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/23 15:20:17 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_elem_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

// if other char in map it will exit 
static void	get_map_size(t_cub *cub, char *line, int fd)
{
	int	rows;

	rows = 0;
	while (is_map_line(line))
	{
		if (!cub->map_width || ft_strlen(line) - 1 > (size_t)cub->map_width)
			cub->map_width = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(fd);
		rows++;
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	cub->map_height = rows;
}

void	allocate_map(char *filename, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = skip_elem_lines(fd);
	get_map_size(cub, line, fd);
	cub->map = malloc(sizeof(char *) * (cub->map_height + 1));
	close(fd);
}
