/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_key_value.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:06:45 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 15:32:10 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_colors(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
}

static int	check_color_value(char *value)
{
	int			i;
	int			j;
	char		**colors;

	i = 0;
	value = trim_spaces(value);
	// printf("string after trim spaces |%s|\n", value);
	// while (value[i])
	// {
	// 	if (!ft_isvalid_path_chars(value[i]))
	// 		return (printf("invalid char in path\n"), 0);
	// 	i++;
	// }
	colors = ft_split(value, ',');
	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
			{
				free_colors(colors);
				free(value);
				return (printf("nonnumeric char\n"), 0); //free
			}
			j++;
		}
		if (ft_atoi(colors[i]) > 255 || ft_atoi(colors[i]) < 0)
		{
			free_colors(colors);
			free(value);
			return (printf("to big nubmers\n"), 0); //free
		}
		i++;
	}
	if (i > 3)
	{
		printf("too many color args\n"); 
		free_colors(colors);
		free(value);
		return (0);
	}
	free_colors(colors);
	free(value);
	return (1);
	// colors: split only numeric chars and commas else error and then split further by commas, 
	// see thet it is valid numbers (0 - 255) 
}

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
	// printf("int i: %i, int j: %i, int end: %i\n", i, j, end);
	// if (i + j >= end)
	// {
	// 	printf("only spaces\n");
	// 	return ;
	// }
	if (i > j)
	{
		tmp = (char *)malloc(1);
		if (!tmp)
			return NULL; // malloc failed
		tmp[0] = '\0';
	}
	else
	{
		// Correct length to allocate (j - i + 1) for inclusive range
		tmp = ft_strndup(&str[i], j - i + 1);
		if (!tmp) return NULL; // malloc failed
	}
	free (str);
	// printf("str in trim spaces: %s\n", str);
	return (tmp);
}

static int	check_path_value(char *value)
{
	int		i;
	int		fd;
	char	*trimmed_value;

	trimmed_value = trim_spaces(value);
	i = 0;
	// printf("str after trim spaces: %s\n", value);
	while (trimmed_value[i])
	{
		if (!ft_isvalid_path_chars(trimmed_value[i]))
		{
			printf("invalid char in path, value[i] %c\n", trimmed_value[i]);
			free(trimmed_value);
			return (0);
		}
		i++;
	}
	// printf("int max path %i\n", PATH_MAX);
	if (i > PATH_MAX)
	{
		free(trimmed_value);
		return (printf("too long path\n"), 0);
	}
	// printf("value %s\n", value);
	fd = open(trimmed_value, O_RDONLY);
	if (fd < 0)
	{
		perror("error opening file\n");
		free(trimmed_value);
		return (0);
	}
	close (fd);
	free(trimmed_value);
	return (1);
	// paths: validate the path and if there are more paths also error
}

int	elemnt_not_found(char *key, t_string *op_line)
{
	if (!ft_strcmp(key, "NO") && op_line->NO == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "SO") && op_line->SO == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "WE") && op_line->WE == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "EA") && op_line->EA == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "F") && op_line->F == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "C") && op_line->C == 1)
		return (printf("duplicate id\n"), 0);
	return (1);
}

void	set_element_as_found(char *key, t_string *op_line)
{
	if (!ft_strcmp(key, "NO"))
		op_line->NO = 1;
	else if (!ft_strcmp(key, "SO"))
		op_line->SO = 1;
	else if (!ft_strcmp(key, "WE"))
		op_line->WE = 1;
	else if (!ft_strcmp(key, "EA"))
		op_line->EA = 1;
	else if (!ft_strcmp(key, "F"))
		op_line->F = 1;
	else if (!ft_strcmp(key, "C"))
		op_line->C = 1;
}

int	is_path_key(char *str)
{
	if(!ft_strcmp(str, "NO") || (!ft_strcmp(str, "SO")) \
	|| (!ft_strcmp(str, "WE")) || (!ft_strcmp(str, "EA")))
		return (1);
	return (0);
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
	}
	else if (len == 1)
	{
		if ((!ft_strcmp(info->key, "F") || !ft_strcmp(info->key, "C")) && elemnt_not_found(info->key, line))
		{
			if (check_color_value(info->value))
				return (set_element_as_found(info->key, line), 1);
			return (0);
		}
	}
	return (printf("invalid id, %s\n", info->key), 0);
}

//11,460 def lost