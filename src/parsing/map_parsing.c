/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 15:08:54 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/20 16:39:59 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' \
	|| c == 'W' || c == 'E' || c == ' ');
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
			return (0);
		while (line[i])
		{
			if (!is_map_char(line[i]) && line[i] != '\n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	map_parsing(char *line, t_cub *cub, int j)
{
	int	i;

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
