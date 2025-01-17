/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 14:02:36 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/17 12:43:30 by eeklund       ########   odam.nl         */
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
	init_line_struct(&line);
	next_line = get_next_line(fd);
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


/*
with map error
==138807== HEAP SUMMARY:
==138807==     in use at exit: 91 bytes in 6 blocks
==138807==   total heap usage: 279 allocs, 273 frees, 7,719 bytes allocated
==138807== 
==138807== 23 bytes in 2 blocks are definitely lost in loss record 1 of 2
==138807==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==138807==    by 0x404AA0: ft_strndup (extra.c:20)
==138807==    by 0x402D08: trim_spaces (check_key_value.c:100)
==138807==    by 0x4033AB: check_color_value (check_key_value.c:35)
==138807==    by 0x403227: valid_key_and_value (check_key_value.c:198)
==138807==    by 0x402B38: check_line (check_line.c:61)
==138807==    by 0x4027D4: valid_input (check.c:55)
==138807==    by 0x4025FD: main (main.c:34)
==138807== 
==138807== 68 bytes in 4 blocks are definitely lost in loss record 2 of 2
==138807==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==138807==    by 0x404AA0: ft_strndup (extra.c:20)
==138807==    by 0x402D08: trim_spaces (check_key_value.c:100)
==138807==    by 0x4032A4: check_path_value (check_key_value.c:114)
==138807==    by 0x403183: valid_key_and_value (check_key_value.c:189)
==138807==    by 0x402B38: check_line (check_line.c:61)
==138807==    by 0x4027D4: valid_input (check.c:55)
==138807==    by 0x4025FD: main (main.c:34)
==138807== 
==138807== LEAK SUMMARY:
==138807==    definitely lost: 91 bytes in 6 blocks
==138807==    indirectly lost: 0 bytes in 0 blocks
==138807==      possibly lost: 0 bytes in 0 blocks
==138807==    still reachable: 0 bytes in 0 blocks
==138807==         suppressed: 0 bytes in 0 blocks
==138807== 
==138807== For lists of detected and suppressed errors, rerun with: -s
==138807== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

these are the hard leaks 
*/