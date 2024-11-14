/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 15:43:30 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/03/01 18:45:56 by nsarmada      ########   odam.nl         */
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

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	n;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	n = 0;
	if (size == 0)
		return (src_len + size);
	while (src[n] != '\0' && dest_len + n < size - 1)
	{
		dest[dest_len + n] = src[n];
		n++;
	}
	dest[dest_len + n] = '\0';
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + src_len);
}

// int main ()
// {
// 	char dest[20] = "heyy";
// 	char src[] = "man";
// 	ft_strlcat(dest, src, 1509);
// 	printf("%s", dest);
// 	return 0;
// }
