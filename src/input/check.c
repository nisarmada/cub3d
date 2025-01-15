/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: elleneklund <elleneklund@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:02:36 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/15 16:35:10 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_line_struct(t_string *op_line)
{
	op_line->elem_count = 0;
	op_line->SO = 0;
	op_line->NO = 0;
	op_line->EA = 0;
	op_line->WE = 0;
	op_line->F = 0;
	op_line->C = 0;
}

static int	is_cub_file(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] != 'b' || str[len - 2] != 'u' || str[len - 3] != 'c' \
	|| str[len - 4] != '.')
		return (0);
	return (1);
}

int	valid_input(int ac, char **av)
{
	int			fd;
	char		*next_line;
	t_string	line;

	if (ac != 2)
		return (printf("Wrong amount of args\n"), 0);
	if (!is_cub_file(av[1]))
		return (printf("Wrong file type, need .cub\n"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Invalid file format"), 0); // error handling msg
	next_line = get_next_line(fd);
	init_line_struct(&line);
	while (next_line != NULL)
	{
		line.line = next_line;
		if (!check_line(&line))
		{
			close(fd);
			free(next_line);
			return (0); //error handling msg and close fd
		}
		free (next_line);
		if (line.elem_count == 6)
			break ;
		next_line = get_next_line(fd);
		while (next_line && !ft_strcmp(next_line, "\n")) //skipping empty lines
		{
			free(next_line);
			next_line = get_next_line(fd);
		}
	}
	close(fd);
	return (1);
}
