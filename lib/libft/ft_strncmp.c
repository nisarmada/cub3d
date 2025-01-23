/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:32:32 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 14:50:28 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL)
		return (1);
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

// int main()
// {
// 	const char s1[] = "1234";
// 	const char s2[] = "1235";
// 	const char s3[] = "bannana";

// 	printf("%d\n", ft_strncmp(s1, s2, 3));
// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	printf("%d\n", ft_strncmp(s1, s3, 4));
// 	return 0;
// }