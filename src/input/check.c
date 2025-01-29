/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:02:36 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/29 14:18:04 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	check_file(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (error_msg("Wrong amount of args\n", 0));
	if (!is_cub_file(av[1]))
		return (error_msg("Wrong file type, need .cub\n", 0));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (error_msg("Error\nCould not open file\n", 0));
	return (fd);
}

char	*skip_empty_lines(int fd)
{
	char	*next_line;

	next_line = get_next_line(fd);
	if (!next_line)
		return (NULL);
	while (next_line && !ft_strcmp(next_line, "\n"))
	{
		free(next_line);
		next_line = get_next_line(fd);
	}
	return (next_line);
}

static int	process_line(t_string *line, char *next_line)
{
	line->line = next_line;
	if (!check_line(line))
	{
		free(next_line);
		return (0);
	}
	free(next_line);
	return (1);
}

// int	check_map_part(int fd, char *cur_line)
// {
// 	char	*prev_line;
// 	char	*next_line;

// 	prev_line = cur_line;
// 	while (cur_line)
// 	{
// 		next_line = get_next_line(fd);
// 		if (!next_line)
// 			break ;
// 		check();
// 		free(prev_line);
// 		prev_line = cur_line;
// 		cur_line = next_line;
// 	}
// }


static int	process_file(int fd)
{
	t_string	line;
	char		*next_line;

	init_line_struct(&line);
	next_line = get_next_line(fd);
	if (!next_line) //FIX: only accept an element, anything else is incorrect. also whitespace. 
		return (error_msg("Error\nEmpty file\n", 0));
	while (next_line && !is_map_line(next_line))
	{
		if (!process_line(&line, next_line))
			return (close(fd), 0);
		next_line = skip_empty_lines(fd);
		if (line.elem_count < 6 && (is_map_line(next_line)))
			return (error_msg("Error\nMissing element\n", 0));
	}
	// check_map_part(fd, next_line);
	if (!finish_file(fd))
	{
		close(fd);
		return(error_msg("Error\nJunk in file\n", 0));
	}
	close(fd);
	if (line.elem_count > 6)
		return(error_msg("Error\nJunk in file\n", 0));
	else if (line.elem_count != 6)
		return (error_msg("Error\nElement not at start of file\n", 0));
	return (1);
}

int	valid_input(int ac, char **av)
{
	int	fd;

	fd = check_file(ac, av);
	if (!fd)
		return (0);
	if (!process_file(fd))
		return (0);
	return (1);
}
