/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 12:30:32 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/29 17:18:00 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_string
{
	char		*line;
	int			elem_count;
	int			elem[6];
	t_key_value	*info;
}	t_string;

//check_key_extras
int		elemnt_not_found(char *key, t_string *op_line);
void	set_element_as_found(char *key, t_string *op_line);
int		is_path_key(char *str);
int		open_file_check(char *trimmed_value);

//free and error
void	free_colors(char **colors, char *value);
int		finish_file(int fd, char *line);
// int		error_msg(char *msg, int status);

//check_line
void	init_line_struct(t_string *op_line);
int		is_cub_file(char *str);

char	*trim_spaces(char *str);
int		check_line(t_string *op_line);
int		valid_key_and_value(t_key_value *info, t_string *op_line);

#endif