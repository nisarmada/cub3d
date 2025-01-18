/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_key_extras.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/18 17:23:00 by nikos         #+#    #+#                 */
/*   Updated: 2025/01/18 17:24:27 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (!ft_strcmp(str, "NO") || (!ft_strcmp(str, "SO")) \
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
