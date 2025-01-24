/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_parsing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/15 14:03:34 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/24 12:29:53 by elleneklund   ########   odam.nl         */
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
	if (!color_string)
		return (NULL);
	*start = end + 1;
	return (color_string);
}

static int	get_rgb_component(char *line, int *component, int *start)
{
	char	*color_string;

	color_string = extract_color_substring(line, start);
	if (!color_string)
		return (-1);
	*component = ft_atoi(color_string);
	free(color_string);
	return (1);
}

int	rgb_toint(char *line, int *cub_color)
{
	t_rgb	tmp_color;
	int		color_int;
	int		start;

	start = 1;
	tmp_color.r = 0;
	tmp_color.b = 0;
	tmp_color.g = 0;
	if (get_rgb_component(line, &tmp_color.r, &start) < 0 || \
	get_rgb_component(line, &tmp_color.g, &start) < 0 || \
	get_rgb_component(line, &tmp_color.b, &start) < 0)
		return (-1);
	color_int = convert_rgb_to_int(tmp_color.r, tmp_color.g, tmp_color.b);
	*cub_color = color_int;
	return (1);
}

int	parse_colors(char *line, t_cub *cub)
{
	if (!ft_strncmp(line, "F", 1))
		return (rgb_toint(line, &cub->floor_color));
	else if (!ft_strncmp(line, "C", 1))
		return (rgb_toint(line, &cub->wall_color));
	return (0);
}
