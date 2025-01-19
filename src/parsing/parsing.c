/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/19 20:17:27 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_cub	*allocate_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
	{
		free(cub);
		return (NULL);
	}
	cub->player->orientation = '\0';
	cub->text = malloc(sizeof(t_text));
	if (!cub->text)
	{
		free(cub->player);
		free(cub);
		return (NULL);
	}
	cub->map_width = 0;
	return (cub);
}

static void	parse_cub_file(char *filename, t_cub *cub) //check with error handling also
{
	int		fd;
	char	*line;
	int		j;

	j = 0;
	allocate_map(filename, cub);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		parse_directions(line, cub);
		parse_colors(line, cub);
		if (is_map_line(line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		map_parsing(line, cub, j);
		j++;
		free(line);
		line = get_next_line(fd);
	}
	cub->map[j] = NULL;
	close(fd);
}

t_cub	*init_parse_cub(char *filename)
{
	t_cub	*cub;
	int		i;

	cub = allocate_cub();
	parse_cub_file(filename, cub);
	cub->player->changed = 0;
	cub->dist_pplane = ((WIN_WIDTH / 2) / tan(0.524));
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	cub->first_render = true;
	//distance from player to projection plan = (projectionplan width / 2) / tan(30 (half of fov)) --> 692
	// printf("dist: %i\n", cub->dist_pplane);
	i = 0;
	while (i < 512)
	{
		cub->keys[i] = false;
		i++;
	}
	return (cub);
}
