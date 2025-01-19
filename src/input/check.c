/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:02:36 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 18:35:30 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (error_msg("Wrong amount of args\n", 0));
	if (!is_cub_file(av[1]))
		return (error_msg("Wrong file type, need .cub\n", 0));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (error_msg("Invalid file format", 0));
	return (fd);
}

char	*skip_empty_lines(int fd)
{
	char	*next_line;

	next_line = get_next_line(fd);
	while (next_line && !ft_strcmp(next_line, "\n"))
	{
		free(next_line);
		next_line = get_next_line(fd);
	}
	return (next_line);
}

int	process_line(int fd, t_string *line, char *next_line)
{
	line->line = next_line;
	if (!check_line(line))
	{
		close(fd);
		free(next_line);
		return (0);
	}
	free(next_line);
	return (1);
}

int	process_file(int fd)
{
	t_string	line;
	char		*next_line;

	init_line_struct(&line);
	next_line = get_next_line(fd);
	while (next_line)
	{
		if (!process_line(fd, &line, next_line))
			return (0);
		if (line.elem_count == 6)
			break ;
		next_line = skip_empty_lines(fd);
	}
	close(fd);
	return (line.elem_count == 6);
}

int	valid_input(int ac, char **av)
{
	int	fd;

	fd = check_file(ac, av);
	if (!fd)
		return (0);
	return (process_file(fd));
}
