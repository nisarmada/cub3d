/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_conversion.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 14:03:34 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/11 15:40:13 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int convert_rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

static t_rgb	get_rgb_values(char *line)
{
	int	start;
	char *color_string;
	t_rgb	rgb;
	int end;

	color_string = NULL;
	start = 1;
	while (line[start] && is_whitespace(line[start]))
		start++;
	while (line[start] && (line[start] >= '0' && line[start] <= '9'))
		start++;
	color_string = ft_substr(line, 2, start - 2);
	rgb.r = ft_atoi(color_string);
	free(color_string);
	end = start + 1;
	while (line[end] && (line[end] >= '0' && line[end] <= '9'))
		end++;
	color_string = ft_substr(line, start + 1, end - start - 1);
	rgb.g = ft_atoi(color_string);
	free(color_string);
	start = end + 1;
	while (line[end] && (line[end] >= '0' && line[end] <= '9'))
		end++;
	color_string = ft_substr(line, start, end - start);
	rgb.b = ft_atoi(color_string);
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
