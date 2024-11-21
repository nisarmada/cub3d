/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:11:17 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/21 16:29:17 by eeklund       ########   odam.nl         */
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
	int		SO;
	int		NO;
	int		WE;
	int		EA;
	int		F;
	int		C;
}	t_string;

int	split_in_two(char *str, t_key_value *info)
{
	int	i;
	int	start;

	i = 0;
	start = i;
	// printf("str in split: %s\n", str);
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i])
	{
		info->key = ft_strndup(&str[start], i);
		info->value = ft_strndup(&str[i], ft_strlen(str) - i);
		// printf("in split\nid: %s\ninfo: %s\n", id_info->id, id_info->info);
		return (1);
	}
	return (0);
}

char	*trim_spaces(char *str)
{
	int		i;
	int		end;
	int		j;
	char	*tmp;

	end = ft_strlen(str) - 1;
	j = end;
	i = 0;
	while (is_whitespace(str[i]))
		i++;
	while (is_whitespace(str[j]))
		j--;
	// printf("int i: %i, int j: %i, int end: %i\n", i, j, end);
	// if (i + j >= end)
	// {
	// 	printf("only spaces\n");
	// 	return ;
	// }
	tmp = ft_strndup(&str[i],j);
	free (str);
	str = tmp;
	// printf("str in trim spaces: %s\n", str);
	return (str);
}

int	check_path_info(char *value)
{
	int	i;
	int	fd;

	value = trim_spaces(value);
	i = 0;
	// printf("str after trim spaces: %s\n", value);
	while (value[i])
	{
		if (!ft_isvalid_path_chars(value[i]))
			return (printf("invalid char in path, value[i] %c\n", value[i]), 0);
		i++;
	}
	// printf("int max path %i\n", PATH_MAX);
	if (i > PATH_MAX)
		return (printf("too long path\n"), 0);
	fd = open(value, O_RDONLY);
	if (fd < 0)
	{
		perror("error opening file\n");
		return (0);
	}
	close (fd);
	return (1);
	// paths: validate the path and if there are more paths also error
}

int	check_colorinfo(char *value)
{
	int			i;
	int			j;
	char		**colors;

	i = 0;
	value = trim_spaces(value);
	// printf("string after trim spaces |%s|\n", value);
	// while (value[i])
	// {
	// 	if (!ft_isvalid_path_chars(value[i]))
	// 		return (printf("invalid char in path\n"), 0);
	// 	i++;
	// }
	colors = ft_split(value, ',');
	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (!ft_isdigit(colors[i][j]))
				return (printf("nonnumeric char\n"), 0);
			j++;
		}
		if (ft_atoi(colors[i]) > 255 || ft_atoi(colors[i]) < 0)
			return (printf("to big nubmers\n"), 0);
		i++;
	}
	if (i > 3)
	{
		printf("too many color args\n");
		free (colors); // also free all the elements in colors
		return (0);
	}
	i = 0;
	// while (colors[i])
	// {
	// 	printf("|%s| ", colors[i]);
	// 	i++;
	// }
	free (colors);

	return (1);
	// colors: split only numeric chars and commas else error and then split further by commas, 
	// see thet it is valid numbers (0 - 255) 
}

void	set_element_as_found(char *key, t_string *op_line)
{
	if (!ft_strcmp(key, "NO"))
		op_line->NO = 1;
	else if (!ft_strcmp(key, "SO"))
		op_line->SO = 1;
	else if (!ft_strcmp(key, "WE"))
		op_line->WE = 1;
	else if (!ft_strcmp(key, "EA"))
		op_line->EA = 1;
	else if (!ft_strcmp(key, "F"))
		op_line->F = 1;
	else if (!ft_strcmp(key, "C"))
		op_line->C = 1;
}

int	elemnt_not_found(char *key, t_string *op_line)
{
	if (!ft_strcmp(key, "NO") && op_line->NO == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "SO") && op_line->SO == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "WE") && op_line->WE == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "EA") && op_line->EA == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "F") && op_line->F == 1)
		return (printf("duplicate id\n"), 0);
	else if (!ft_strcmp(key, "C") && op_line->C == 1)
		return (printf("duplicate id\n"), 0);
	return (1);
}

int	is_path_id(char *str)
{
	if(!ft_strcmp(str, "NO") || (!ft_strcmp(str, "SO")) \
	|| (!ft_strcmp(str, "WE")) || (!ft_strcmp(str, "EA")))
		return (1);
	return (0);
}


static int	valid_id_and_value(t_key_value *info, t_string *op_line)
{
	int		len;
	char	*key;
	char	*value;

	key = info->key;
	value = info->value;
	len = ft_strlen(key);
	if (len == 2)
	{
		if (is_path_id(key) && elemnt_not_found(key, op_line))
		{
			if (!check_path_info(value))
				return (0);
			set_element_as_found(key, op_line);
			return (1);
		}
	}
	else if (len == 1)
	{
		if ((!ft_strcmp(key, "F") || !ft_strcmp(key, "C")) && elemnt_not_found(key, op_line))
		{
			if (!check_colorinfo(value))
				return (0);
			set_element_as_found(key, op_line);
			return (1);
		}
	}
	return (printf("invalid id, %s\n", key), 0);
	// validate the information two different funcs for paths and colors
}

static int	check_line(t_string *op_line)
{
	int			i;
	char		*str;
	t_key_value	info;

	i = 0;
	str = op_line->line;
	while (is_whitespace(str[i])) // take away whitespace in beginning of line
		i++;
	if (str[i])
	{
		printf("str %s\n", &str[i]);
		if (!split_in_two(&str[i], &info))
			return (printf("have to divide id and info with space\n"), 0); // split the line in two parts, by the first whitespace/ space
		// printf("id: %s\ninfo: %s\n", info.key, info.value);
		if (!valid_id_and_value(&info, op_line)) // validate the identifier
		{
			// free(info.key);
			// free(info.value);
			return (0);
		}
		op_line->elem_count++;
		// free(info.key);
		// free(info.value);
		return (1);
	}
	// free(info.key);
	// free(info.value);
	return (printf("only whitespace on line\n"), 0); // maybe we say this is fine?? 
}

void	init_op_line(t_string *op_line)
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
	char		*line;
	t_string	op_line;

	if (ac != 2)
		return (printf("Wrong amount of args\n"), 0);
	if (!is_cub_file(av[1]))
		return (printf("Wrong file type, need .cub\n"), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Invalid file format"), 0); // error handling msg
	line = get_next_line(fd);
	init_op_line(&op_line);
	while (line != NULL)
	{
		op_line.line = line;
		if (!check_line(&op_line))
			return (free (line), 0); //error handling msg and close fd
		free (line);
		// printf("line is gooood\n ----------------------------------- \n");
		line = get_next_line(fd);
		while (line && !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (op_line.elem_count == 6) // can be above the while loop and the get_next_line
			break ;
	}
	// op_line.line = line;
	// printf("line %s\n", line);

	// if (!check_map(line, fd))
	// 	return (0); // error handling msg
	close(fd);
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