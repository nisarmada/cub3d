/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 10:27:40 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_map(char *filename, t_cub *cub)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(filename, O_RDONLY);
	rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	while (is_map_line(line))
	{
		if (!cub->map_width || ft_strlen(line) - 1 > (size_t)cub->map_width)
			cub->map_width = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(fd);
		rows++;
	}
	if (line)
		free(line);
	cub->map_height = rows;
	cub->map = malloc(sizeof(char *) * (rows + 1));
	return (fd);
	// close(fd);
}

static void	parse_cub_file(char *filename, t_cub *cub) //check with error handling also
{
	int		fd = 0;
	char	*line;
	int		j;

	j = 0;
	int old_fd = allocate_map(filename, cub);
	fd = open(filename, O_RDONLY);
	close(old_fd);
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
	while (is_map_line(line))
	{
		map_parsing(line, cub, j);
		j++;
		free(line);
		line = get_next_line(fd);
	}
	cub->map[j] = NULL;
	close(fd);
}

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

t_cub	*init_cub(char *filename)
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
