/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 15:11:08 by nikos         #+#    #+#                 */
/*   Updated: 2023/10/13 13:38:49 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)&p[i]);
		i++;
	}
	return (NULL);
}

// #include <string.h>
// int main ()
// {
//     int s1[] = {1, 2, 3, 4, 5};
//     char s2[] = "hall.oo";

//     printf("%p\n", ft_memchr(s1, 3, 5));
//     printf("%p\n", ft_memchr(s2, 'a', 6));
//     printf("%p\n", ft_memchr(s2, 'a', 1));
//     printf("original :%p\n", ft_memchr(s1, 3, 5));
//     printf("original :%p\n", ft_memchr(s2, 'a', 6));
//     printf("original :%p\n", ft_memchr(s2, 'a', 1));
//     return 0;

// }