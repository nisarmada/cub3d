/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_key_extras.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: elleneklund <elleneklund@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 16:57:31 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/19 18:21:10 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (NULL);
	free (str);
	return (tmp);
}
