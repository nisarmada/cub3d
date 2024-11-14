/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 16:36:27 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/06/08 12:27:28 by snijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	if (size == 0)
		return (src_len);
	dest[i] = '\0';
	return (src_len);
}

// int main()
// {
// 	int i = 0;
// 	char dest[4];
// 	char src[] = "yooor";
// 	ft_strlcpy(dest, src, 4);
// 	while (i < 4)
// 	{
// 		printf("%c\n", dest[i]);
// 		i++;
// 	}
// 	printf("%s", dest);
// 	return 0;
// }
