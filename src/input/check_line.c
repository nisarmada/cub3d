/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:04:40 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/27 08:25:05 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	init_line_struct(t_string *op_line)
{
	int	i;

	op_line->elem_count = 0;
	i = 0;
	while (i < 6)
	{
		op_line->elem[i] = 0;
		i++;
	}
}

int	is_cub_file(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] != 'b' || str[len - 2] != 'u' || str[len - 3] != 'c' \
	|| str[len - 4] != '.')
		return (0);
	return (1);
}

static void	free_info(t_key_value *info)
{
	if (info)
	{
		free(info->key);
		free(info);
	}
}

static t_key_value	*split_in_two(char *str)
{
	int			i;
	int			start;
	t_key_value	*info;

	i = 0;
	start = i;
	info = malloc(sizeof(t_key_value));
	if (!info)
		return (NULL);
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i])
	{
		info->key = ft_strndup(&str[start], i);
		info->value = ft_strndup(&str[i], ft_strlen(str) - i);
		return (info);
	}
	return (free(info), NULL);
}

int	check_line(t_string *line)
{
	int			i;
	char		*cur_fileline;
	t_key_value	*info;

	i = 0;
	cur_fileline = line->line;
	info = NULL;
	while (is_whitespace(cur_fileline[i]))
		i++;
	if (cur_fileline[i])
	{
		info = split_in_two(&cur_fileline[i]);
		if (!info)
			return (error_msg("Error\nCould not find ID and value\n", 0));
		if (!valid_key_and_value(info, line))
			return (free_info(info), 0);
		line->elem_count++;
		free_info(info);
		return (1);
	}
	return (1);
}