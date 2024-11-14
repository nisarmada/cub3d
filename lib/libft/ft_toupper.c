/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 16:24:04 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:40:57 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c);
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// int main ()
// {
// 	int a = 'a';
// 	int b = 'B';

// 	printf("%c\n", ft_toupper(a));
// 	printf("%c\n", ft_toupper(b));
// 	return 0;
// }