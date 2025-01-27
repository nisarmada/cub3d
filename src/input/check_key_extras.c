/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_key_extras.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 16:57:31 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/27 15:39:09 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	elemnt_not_found(char *key, t_string *op_line)
{
	if (!ft_strcmp(key, "NO") && op_line->elem[0] == 1)
		return (0);
	else if (!ft_strcmp(key, "SO") && op_line->elem[1] == 1)
		return (0);
	else if (!ft_strcmp(key, "WE") && op_line->elem[2] == 1)
		return (0);
	else if (!ft_strcmp(key, "EA") && op_line->elem[3] == 1)
		return (0);
	else if (!ft_strcmp(key, "F") && op_line->elem[4] == 1)
		return (0);
	else if (!ft_strcmp(key, "C") && op_line->elem[5] == 1)
		return (0);
	return (1);
}

void	set_element_as_found(char *key, t_string *op_line)
{
	if (!ft_strcmp(key, "NO"))
		op_line->elem[0] = 1;
	else if (!ft_strcmp(key, "SO"))
		op_line->elem[1] = 1;
	else if (!ft_strcmp(key, "WE"))
		op_line->elem[2] = 1;
	else if (!ft_strcmp(key, "EA"))
		op_line->elem[3] = 1;
	else if (!ft_strcmp(key, "F"))
		op_line->elem[4] = 1;
	else if (!ft_strcmp(key, "C"))
		op_line->elem[5] = 1;
}

int	is_path_key(char *str)
{
	if (!ft_strcmp(str, "NO") || (!ft_strcmp(str, "SO")) \
	|| (!ft_strcmp(str, "WE")) || (!ft_strcmp(str, "EA")))
		return (1);
	return (0);
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
	if (i > j)
		tmp = ft_strdup("");
	else
		tmp = ft_strndup(&str[i], j - i + 1);
	if (!tmp)
		return (free(str), NULL);
	free (str);
	return (tmp);
}

int	open_file_check(char *trimmed_value)
{
	int	fd;

	fd = open(trimmed_value, O_RDONLY);
	if (fd < 0)
	{
		error_msg_spec("Error\nFailed to open file: ", trimmed_value, 0);
		close(fd);
		free(trimmed_value);
		return (0);
	}
	close (fd);
	return (1);
}
