/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_key_value.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:06:45 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 17:03:25 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_spaces(char *str)
{
	int		i;
	int		j;
	int		end;
	char	*tmp;

	end = ft_strlen(str) - 1;
	j = end;
	i = 0;
	while (is_whitespace(str[i]))
		i++;
	while (j >= i && is_whitespace(str[j]))
		j--;
	if (i > j)
		tmp = ft_strdup("");
	else
		tmp = ft_strndup(&str[i], j - i + 1);
	if (!tmp)
		return (NULL);
	free (str);
	return (tmp);
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
				return (free_colors(colors, value), error_msg("nonnumeric char\n", 0)); //free 2 commas or more alters the color.. 
			j++;
		}
		if (ft_atoi(colors[i]) > 255 || ft_atoi(colors[i]) < 0)
			return (free_colors(colors, value), \
			error_msg("to big numbers\n", 0));
		i++;
	}
	if (i > 3)
		return (free_colors(colors, value), \
		error_msg("too many color args\n", 0));
	free_colors(colors, value);
	return (1);
}

static int	check_path_value(char *value)
{
	int		i;
	int		fd;
	char	*trimmed_value;

	trimmed_value = trim_spaces(value);
	i = 0;
	while (trimmed_value[i])
	{
		if (!ft_isvalid_path_chars(trimmed_value[i]))
		{
			printf("invalid char in path, value[i] %c\n", trimmed_value[i]);
			return (free(trimmed_value), 0);
		}
		i++;
	}
	if (i > PATH_MAX)
		return (free(trimmed_value), error_msg("too long path\n", 0));
	fd = open(trimmed_value, O_RDONLY);
	if (fd < 0)
		return (free(trimmed_value), error_msg("error opening file\n", 0));
	close (fd);
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
			return (0); // error msg?
		}
	}
	else if (len == 1)
	{
		if ((!ft_strcmp(info->key, "F") || !ft_strcmp(info->key, "C")) && elemnt_not_found(info->key, line))
		{
			if (check_color_value(info->value))
				return (set_element_as_found(info->key, line), 1);
			return (0); //error msg?
		}
	}
	return (printf("invalid id, %s\n", info->key), 0);
}

//11,460 def losxt