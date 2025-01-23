/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_conversion.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 14:03:34 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 15:21:36 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	convert_rgb_to_int(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

static char	*extract_color_substring(char *line, int *start)
{
	int		end;
	char	*color_string;

	while (line[*start] && is_whitespace(line[*start]))
		(*start)++;
	end = *start;
	while (line[end] && (line[end] >= '0' && line[end] <= '9'))
		end++;
	color_string = ft_substr(line, *start, end - *start);
	*start = end + 1;
	return (color_string);
}

static	t_rgb	get_rgb_values(char *line)
{
	t_rgb	rgb;
	char	*color_string;
	int		start;

	start = 1;
	color_string = extract_color_substring(line, &start);
	rgb.r = ft_atoi(color_string);
	free(color_string);

	color_string = extract_color_substring(line, &start);
	rgb.g = ft_atoi(color_string);
	free(color_string);

	color_string = extract_color_substring(line, &start);
	rgb.b = ft_atoi(color_string);
	free(color_string);

	return (rgb);
}

void	parse_colors(char *line, t_cub *cub)
{
	t_rgb	floor;
	t_rgb	wall;
	int		color_int;

	(void)cub;
	(void) wall;
	if (!ft_strncmp(line, "F", 1))
	{
		floor = get_rgb_values(line);
		color_int = convert_rgb_to_int(floor.r, floor.g, floor.b);
		cub->floor_color = color_int;
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		wall = get_rgb_values(line);
		color_int = convert_rgb_to_int(wall.r, wall.g, wall.b);
		cub->wall_color = color_int;
	}
}
