/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 15:43:44 by nikos         #+#    #+#                 */
/*   Updated: 2023/10/13 19:12:25 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*p1;
	const unsigned char		*p2;

	i = 0;
	p1 = s1;
	p2 = s2;
	while (i < n && p1[i] == p2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((p1[i] - p2[i]));
}

// #include <string.h>

// int main ()
// {
//    char test1[] = "helloo world";
//    char test2[] = "helloo aworld";

//    printf("mine: %d\n", ft_memcmp(test1, test2, 15));
//    printf("original: %d\n", memcmp(test1, test2, 15));

//    char test3[] = "";
//    char test4[] = "";

//    printf("mine: %d\n", ft_memcmp(test3, test4, 2));
//    printf("original: %d\n", memcmp(test3, test4, 2));

//    int test5[] = {-1, -2, -3};
//    int test6[] = {1, 2, 3};

//    printf("mine: %d\n", ft_memcmp(test5, test6, sizeof(test5)));
//    printf("original: %d\n", memcmp(test5, test6, sizeof(test5)));

//    return 0;
// }