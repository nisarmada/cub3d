/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_key_value.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:06:45 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/29 17:05:13 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	check_color_interval(char **colors, int i, char *value)
{
	int	color_int;

	color_int = ft_atoi(colors[i]);
	if (color_int > 255 || color_int < 0)
	{
		free_colors(colors, value);
		return (error_msg("Error\nColor value not in scope, "\
		"only accept value between 0-255\n", 0));
	}
	return (1);
}

int	check_arg_count(int i, char **colors, char *value)
{
	int	j;

	if (i > 3)
	{
		free_colors(colors, value);
		return (error_msg("Error\nToo many color args\n", 0));
	}
	j = 0;
	while (value[j] && value[j + 1])
	{
		if (value[j] == ',' && value[j] == value[j + 1])
			return (error_msg("Error\nAdjacent commas\n", 0));
		j++;
	}
	return (1);
}

static int	check_color_value(char *value)
{
	int			i;
	int			j;
	char		**colors;

	value = trim_spaces(value);
	colors = ft_split(value, ',');
	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
				return (free_colors(colors, value), \
				error_msg("Error\nNonnumeric char in color value\n", 0));
			j++;
		}
		if (!check_color_interval(colors, i, value))
			return (0);
		i++;
	}
	if (!check_arg_count(i, colors, value))
		return (0);
	free_colors(colors, value);
	return (1);
}

static int	check_path_value(char *value)
{
	int		i;
	char	*trimmed_value;

	trimmed_value = trim_spaces(value);
	i = 0;
	while (trimmed_value[i])
	{
		if (!ft_isvalid_path_chars(trimmed_value[i]))
		{
			free(trimmed_value);
			return (error_msg("Error\nInvalid char in path\n", 0));
		}
		i++;
	}
	if (i > PATH_MAX)
	{
		free(trimmed_value);
		return (error_msg("Error\nToo long path\n", 0));
	}
	if (!open_file_check(trimmed_value))
		return (0);
	free(trimmed_value);
	return (1);
}

int	valid_key_and_value(t_key_value *info, t_string *line)
{
	int	len;

	len = ft_strlen(info->key);
	if (len == 2)
	{
		if (is_path_key(info->key) && elemnt_not_found(info->key, line))
		{
			if (check_path_value(info->value))
				return (set_element_as_found(info->key, line), 1);
			return (0);
		}
		return (free(info->value), error_msg("Error\nDuplicate ID\n", 0));
	}
	else if (len == 1)
	{
		if ((!ft_strcmp(info->key, "F") || !ft_strcmp(info->key, "C")) && \
		elemnt_not_found(info->key, line))
		{
			if (check_color_value(info->value))
				return (set_element_as_found(info->key, line), 1);
			return (0);
		}
		return (free(info->value), error_msg("Error\nDuplicate ID\n", 0));
	}
	return (error_msg("Error\nInvalid ID\n", 0));
}
