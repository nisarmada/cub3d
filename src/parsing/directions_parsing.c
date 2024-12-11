/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directions_parsing.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: elleneklund <elleneklund@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 15:15:45 by elleneklund   #+#    #+#                 */
/*   Updated: 2024/12/11 15:21:55 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *find_path(char *file)
{
	int		start;
	int		end;
	char	*path;

	start = 2;
	path = NULL;
	// printf("whitespace %i\n", is_whitespace(file[start]));
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
