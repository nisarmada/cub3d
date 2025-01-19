/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:04:40 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 16:55:35 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_key_value	*split_in_two(char *str)
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

void	free_info(t_key_value *info)
{
	free(info->key);
	free(info);
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
			return (error_msg("have to divide id and info with space\n", 0));
		if (!valid_key_and_value(info, line))
			return (free_info(info), 0);
		line->elem_count++;
		free_info(info);
		return (1);
	}
	free_info(info);
	return (error_msg("only whitespace on line\n", 0)); // maybe we say this is fine?? 
}
