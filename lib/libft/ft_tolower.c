/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 16:36:47 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:40:51 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c);
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// int main ()
// {
// 	int a = 'a';
// 	int b = 'B';

// 	printf("%c\n", ft_tolower(a));
// 	printf("%c\n", ft_tolower(b));
// 	return 0;
// }