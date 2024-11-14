/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:37:21 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:38:58 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dest;
	const unsigned char	*byte_src;
	size_t				i;

	byte_dest = (unsigned char *)dest;
	byte_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		byte_dest[i] = byte_src[i];
		i++;
	}
	return (dest);
}

/*int main()
{
	int src_arr[] = {1, 2, 3, 4, 5};
	int dest_arr[5];
	int i = 0;

	ft_memcpy(dest_arr, src_arr, sizeof(src_arr));
	while (i < sizeof(src_arr) / sizeof(src_arr[0]))
	{
		printf("%d\n", dest_arr[i]);
		i++;
	}
	return 0;
}*/