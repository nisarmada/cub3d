/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:04:40 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/15 20:01:26 by eeklund       ########   odam.nl         */
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
		// printf("in split\nid: %s\ninfo: %s\n", id_info->id, id_info->info);
		return (info);
	}
	return (free(info), NULL);
}

void	free_info(t_key_value *info)
{
	free(info->key);
	// free(info->value); // this was the thing giving the double free, but whyyyyy??
	free(info);
}

int	check_line(t_string *line)
{
	int			i;
	char		*cur_fileline;
	t_key_value	*info;

	i = 0;
	cur_fileline = line->line; //(malloced from gnl)
	info = NULL;
	while (is_whitespace(cur_fileline[i])) // take away whitespace in beginning of line
		i++;
	if (cur_fileline[i])
	{
		info = split_in_two(&cur_fileline[i]);
		if (!info)
			return (printf("have to divide id and info with space\n"), 0); // split the line in two parts, by the first whitespace/ space
		if (!valid_key_and_value(info, line)) // validate the identifier
			return (free_info(info), 0);
		line->elem_count++;
		free_info(info);
		// printf("hello\n");
		return (1);
	}
	free_info(info);
	return (printf("only whitespace on line\n"), 0); // maybe we say this is fine?? 
}