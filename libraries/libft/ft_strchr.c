/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:08:52 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/28 00:18:35 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int main() {
//     const char *str = "teste";
//     char c = '\0';

//     char *result = ft_strchr(str, c);

//     printf("Result: %p\n", result);

//     return 0;
// }