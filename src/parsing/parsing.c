/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/18 20:21:07 by eeklund       ########   odam.nl         */
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

void parse_directions(char *line, t_cub *cub)
{
	char *path;
	
	// printf("line: %s\n", line);
	if (!ft_strncmp(line, "NO", 2))
	{
		path = find_path(line);
		cub->north = path;
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		path = find_path(line);
		cub->south = path;
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		path = find_path(line);
		cub->west = path;
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		path = find_path(line);
		cub->east = path;
	}
}

void parse_cub_file(char *filename, t_cub *cub)
{
	int		fd;
	char	*line;
	int		j;

	j = 0;
	(void)cub;
	allocate_map(filename, cub);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		line = trim_spaces(line); // ellen added this line
		parse_directions(line, cub);
		parse_colors(line, cub);
	//	printf("line is %s\n", line);
		if (!ft_strncmp(line, "1", 1) || !ft_strncmp(line, "0", 1))
		{
			map_parsing(line, cub, j);
			//printf("map[%i] %s\n", j, cub->map[j]);
			
		}
		line = get_next_line(fd);
	}
	close(fd);
}


char *find_path(char *file)
{
	int		start;
	int		end;
	char	*path;

	start = 2;
	path = NULL;
	//printf("whitespace %i\n", is_whitespace(file[start]));
	while (is_whitespace(file[start]))
		start++;
	end = start;
	while (file[end] && !is_whitespace(file[end]))
        end++;
	//printf("start %i end %i\n", start, end);
	path = ft_substr(file, start, end - start);
	// printf("path %s\n", path);
	return (path);
}
