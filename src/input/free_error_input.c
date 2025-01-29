/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error_input.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 16:57:54 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/29 17:11:57 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_colors(char **colors, char *value)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
	free(value);
}

int	finish_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && !ft_strcmp(line, "\n"))
	{
		free (line);
		line = skip_empty_lines(fd);
	}
	if (line)
	{
		free (line);
		return (0);
	}
	return (1);
}

int	error_msg(char *msg, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (status);
}

int	error_msg_spec(char *msg, void *spec, int status)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(spec, STDERR_FILENO);
	write(2, "\n", 1);
	return (status);
}
