/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 15:08:54 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/11/22 17:39:17 by elleneklund   ########   odam.nl         */
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
		rows++;
		if (!cub->map_width || ft_strlen(line) - 1 > (size_t)cub->map_width)
			cub->map_width = ft_strlen(line) - 1;
		line = get_next_line(fd);
	}
	//printf("this many rows %i\n", rows);
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
}

int is_valid_map(t_cub *cub)
{
	int	i;
	int	j;
	
}