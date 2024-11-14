/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 17:48:31 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/16 17:04:02 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (!little[0] || !little)
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		n = 0;
		while (big[i + n] == little[n] && big[i + n] && i + n < len)
		{
			n++;
		}
		if (!little[n])
		{
			return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

// #include <string.h>

// int main ()
// {
// 	const char test1[] = "aaabcabcd";
// 	const char test2[] = "cd";

// 	printf("mine: %s\n", ft_strnstr(test1, test2, 8));
// 	// printf("original: %s", strnstr(test1, test2, 0));
// 	return 0;
// }