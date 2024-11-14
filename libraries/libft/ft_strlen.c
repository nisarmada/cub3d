/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 16:46:45 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/03/01 18:30:21 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int main ()
// {
// 	char str1[] = "kalimera";
// 	char str2[] = "yoo";

// 	printf("%d\n", ft_strlen(str1));
// 	printf("%d\n", ft_strlen(str2));
// 	return 0;
// }