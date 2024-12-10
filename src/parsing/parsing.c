/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/07 16:31:32 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cub *initialize_cub(void)
{
	t_cub *cub;

    // Allocate memory for cub
    cub = malloc(sizeof(t_cub));
    if (!cub)
        return (NULL);

    // Allocate memory for player
    cub->player = malloc(sizeof(t_player));
    if (!cub->player)
    {
        // If player allocation fails, free cub and return NULL
        free(cub);
        return (NULL);
    }
	// cub->text = malloc (sizeof(t_text));
	// if (!cub->text)
	// {
	// 	free(cub->player);
	// 	free(cub);
	// 	return (NULL);
	// }
    // Initialize player fields to 0 or default values
    cub->player->x = 0;
    cub->player->y = 0;
    cub->player->angle = 0;
    cub->player->fov = 0;
    cub->player->orientation = '\0';

    // Initialize other fields
    cub->east = NULL;
    cub->west = NULL;
    cub->north = NULL;
    cub->south = NULL;
    cub->map = NULL;
    cub->mlx = NULL;
    cub->img = NULL;
	// cub->text = NULL;
	cub->dist_pplane = 692;
	for (int i = 0; i < 256; i++)
		cub->keys[i] = false;
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
		// line = trim_spaces(line); // ellen added this line
		parse_directions(line, cub);
		parse_colors(line, cub);
		if (is_map_line(line))
			break;
		line = get_next_line(fd);
	}
	while (line)
	{
		map_parsing(line, cub, j);
		j++;
		line = get_next_line(fd);
	}
	cub->map[j] = NULL;
	close(fd);
}

char *find_path(char *file)
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

void find_player_position(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cub->map[j])
	{
		i = 0;
		while (cub->map[j][i])
		{
			if (cub->map[j][i] == 'N' || cub->map[j][i] == 'S'
				|| cub->map[j][i] == 'W' || cub->map[j][i] == 'E')
			{
				cub->player->x = i * TILE_SIZE + TILE_SIZE / 2;
				cub->player->y = j * TILE_SIZE + TILE_SIZE / 2;
				cub->player->orientation = cub->map[j][i];
				define_field_of_vision(cub);
			}
			i++;
		}
		j++;
	}
}

void define_field_of_vision(t_cub *cub)
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