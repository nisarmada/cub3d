/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:11:17 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/14 16:56:25 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/* 
open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday
*/

#include "cub3d.h"


// static int	check_line(char *line)
// {

// }

int	valid_input(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		// if (!check_line(line))
			// return (free (line), 0);
		free (line);
		line = get_next_line(fd);
	}
	return (1);
}

/*

element rules:
elements can be separated by only empty lines!
always the identifier first
indentifier consists of 1 or 2 characters


map rules:
no empty lines
only valid chars are 0, 1, N, S , E and W
first line must be all 1 or space
first of all rows must be 1
last of all rows must be 1
last line must be all 1 or space
*/
