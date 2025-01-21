/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 14:55:23 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/21 11:57:13 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
	}
	return (count);
}

static size_t	len_calc(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}

static char	**free_all(char **s, size_t count)
{
	while (count > 0)
	{
		free(s[count - 1]);
		count--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**d;
	size_t	count;

	count = 0;
	i = word_count(s, c);
	d = (char **)malloc(sizeof(char *) * (i + 1));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			d[count] = ft_substr(s, i, len_calc(&s[i], c));
			if (d[count] == NULL)
				return (free_all(d, count));
			count++;
			i = i + len_calc(&s[i], c);
		}
	}
	d[count] = NULL;
	return (d);
}

// int main ()
// {
// 	char const s[] = "--1hgfh-2--3---4----5-----42-- ---gsdgsdf4234";
// 	char c = '-';
// 	int i = 0;
// 	char **d = ft_split(s, c);
// 	while (d[i])
// 	{
// 		printf("%s\n", d[i]);
// 		i++;
// 	}
// 	free_all(d, 8);
// 	return 0;
// }