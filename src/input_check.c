/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:11:17 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/15 18:04:21 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/* 
open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday
*/

#include "cub3d.h"


typedef struct	s_string
{
	char	*line;
	int		elem_count;
}	t_string;

// static int	check_line(t_string *op_line)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = op_line->line;
// 	while (is_whitespace(str[i]))
// 		i++;
// 	if (str[i])
// 	{
// 		if (!ft_strncmp(&str[i], "F", 1) || !ft_strncmp(&str[i], "C", 1)\
// 		&& is_whitespace(str[i + 1])) 
// 	}
// 	if (str[i])
// 	{
// 		if (!ft_strncmp(&str[i], "NO", 2) || !ft_strncmp(&str[i], "SO", 2)\
// 		|| !ft_strncmp(&str[i], "WE", 2) || !ft_strncmp(&str[i], "EA", 2))
// 	}
// 	op_line->elem_count++;
// 	return (1);
// }

// int	check_first_line(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if ()
// 	}
// }

// static int	check_map(char	*line, int fd)
// {
// 	char	*cur_line;
// 	char	*next_line;

// 	if (!check_first_line(line)) // need to create
// 		return (free(line), 0); // error handling
// 	free(line);
// 	cur_line = get_next_line(fd);
// 	next_line = get_next_line(fd);
// 	while (next_line)
// 	{
// 		if (!check_map_line(cur_line)) // need to create
// 			return (free(cur_line), 0);
// 		free(cur_line);
// 		cur_line = next_line;
// 		next_line = get_next_line(fd);
// 	}
// 	if (!check_last_line(cur_line))
// 		return (free(cur_line), 0); // error handling 
// 	free(cur_line);
// 	return (1);
// }

int	valid_input(int ac, char **av)
{
	int			fd;
	char		*line;
	t_string	op_line;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0); // error handling msg
	line = get_next_line(fd);
	op_line.elem_count = 0;
	while (line != NULL)
	{
		op_line.line = line;
		// if (!check_line(&op_line))
		// 	return (free (line), 0); //error handling msg
		free (line);
		line = get_next_line(fd);
		if (op_line.elem_count == 6)
			break ;
	}
	op_line.line = line;
	// if (!check_map(line, fd))
	// 	return (0); // error handling msg
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
