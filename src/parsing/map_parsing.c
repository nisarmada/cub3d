/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 15:08:54 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/29 17:42:52 by eeklund       ########   odam.nl         */
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
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	cub->map[j] = malloc(sizeof(char) * cub->map_width + 1);
	if (!cub->map[j])
		return ;
	while (i < (int)len)
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
