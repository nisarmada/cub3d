/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   direction_parsing.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 12:44:28 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/24 12:40:13 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	char	*find_path(char *file)
{
	int		start;
	int		end;
	char	*path;

	start = 2;
	path = NULL;
	while (is_whitespace(file[start]))
		start++;
	end = start;
	while (file[end] && !is_whitespace(file[end]))
		end++;
	path = ft_substr(file, start, end - start);
	if (!path)
		return (NULL);
	return (path);
}

static int	assign_path(char *line, char **direction)
{
	char	*path;

	path = find_path(line);
	if (!path)
		return (-1);
	*direction = path;
	return (1);
}

int	parse_directions(char *line, t_cub *cub)
{
	if (!ft_strncmp(line, "NO", 2))
		assign_path(line, &cub->north);
	else if (!ft_strncmp(line, "SO", 2))
		assign_path(line, &cub->south);
	else if (!ft_strncmp(line, "WE", 2))
		assign_path(line, &cub->west);
	else if (!ft_strncmp(line, "EA", 2))
		assign_path(line, &cub->east);
	return (0);
}
