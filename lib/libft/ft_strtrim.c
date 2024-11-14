/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:22:55 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/03/01 18:47:24 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*d;
// 	size_t	len;
// 	size_t	i;

// 	i = 0;
// 	len = ft_strlen(s);
// 	d = malloc(len + 1);
// 	if (d == NULL)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// 	d[i] = '\0';
// 	return (d);
// }

static int	char_found(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		front;
	size_t		back;
	size_t		i;
	char		*ptr;

	front = 0;
	i = 0;
	back = ft_strlen(s1);
	while (s1[front] && char_found(s1[front], set))
		front++;
	while (back > front && char_found(s1[back - 1], set))
		back--;
	if ((back - front) == 0)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * ((back - front) + 1));
	if (ptr == NULL)
		return (NULL);
	while (front < back)
	{
		ptr[i] = s1[front];
		i++;
		front++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main ()
// {
// 	char const *set = "acb";
// 	char const *s = "abcdba";
// 	char *ptr = ft_strtrim(s, set);
// 	printf("%s", ptr);

// 	free(ptr);
// 	return 0;
// }