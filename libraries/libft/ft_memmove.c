/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:46:56 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:39:02 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dest;
	const unsigned char	*byte_src;
	unsigned char		buffer[100000];
	size_t				i;

	byte_dest = (unsigned char *)dest;
	byte_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		buffer[i] = byte_src[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		byte_dest[i] = buffer[i];
		i++;
	}
	return (dest);
}

// int main()
// {
// 	char arr_dest[4];
// 	char arr_src[] = "yooo";
// 	int i = 0;

// 	ft_memmove(arr_dest, arr_src, sizeof(arr_src));
// 	while (i < sizeof(arr_src) / sizeof(arr_src[i]))
// 	{
// 		printf("%c\n", arr_dest[i]);
// 		i++;
// 	}
// }