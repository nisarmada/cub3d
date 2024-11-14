/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 11:54:19 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/05/17 17:18:21 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 24
#endif
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

char	*free_secure(char **str)
{
	free(*str);
	*str = NULL;
	return (*str);
}

char	*read_str(int fd, char *str)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_secure(&str));
	read_bytes = 1;
	while (!ft_strchr(str, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free_secure(&buffer);
			return (free_secure(&str));
		}
		buffer[read_bytes] = '\0';
		str = ft_strjoin(str, buffer);
		if (!str)
			return (free_secure(&buffer));
	}
	free(buffer);
	return (str);
}

char	*get_new_line(char *leftover_line)
{
	int		i;
	char	*str;

	i = 0;
	if (!leftover_line || *leftover_line == '\0')
		return (NULL);
	while (leftover_line[i] && leftover_line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (leftover_line[i] && leftover_line[i] != '\n')
	{
		str[i] = leftover_line[i];
		i++;
	}
	if (leftover_line[i] == '\n')
	{
		str[i] = leftover_line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_leftover_line(char *leftover_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (leftover_line[i] != '\0' && leftover_line[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (ft_strlen(leftover_line) - i + 1));
	if (!str)
		return (free_secure(&leftover_line));
	if (leftover_line[i] != '\0')
		i++;
	while (leftover_line[i] != '\0')
	{
		str[j] = leftover_line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(leftover_line);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*leftover_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	leftover_line = read_str(fd, leftover_line);
	if (!leftover_line)
		return (NULL);
	line = get_new_line(leftover_line);
	if (!line)
		return (free_secure(&leftover_line));
	leftover_line = get_leftover_line(leftover_line);
	return (line);
}
