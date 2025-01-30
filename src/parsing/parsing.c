/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/30 12:14:09 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*parse_elem(t_cub *cub, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (parse_directions(line, cub) < 0)
			return (free(line), NULL);
		if (parse_colors(line, cub) < 0)
			return (free(line), NULL);
		if (is_map_line(line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	read_map_lines(t_cub *cub, char *line, int fd)
{
	int	j;

	j = 0;
	while (is_map_line(line))
	{
		map_parsing(line, cub, j);
		j++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	cub->map[j] = NULL;

}

static int	parse_cub_file(char *filename, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = 0;
	if (!allocate_map(filename, cub))
	{
		free(cub->player);
		free(cub->text);
		return (free(cub), 0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = parse_elem(cub, fd);
	if (!line)
		return (0);
	read_map_lines(cub, line, fd);
	close(fd);
	return (1);
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
	if (!cub)
		return (NULL);
	if (!parse_cub_file(filename, cub))
		return (NULL);
	cub->player->changed = 0;
	cub->dist_pplane = ((WIN_WIDTH / 2) / tan(0.524));
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	cub->first_render = true;
	i = 0;
	while (i < 512)
	{
		cub->keys[i] = false;
		i++;
	}
	return (cub);
}
