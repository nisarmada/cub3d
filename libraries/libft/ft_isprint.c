/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 16:26:30 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:38:40 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

	// int main()
	// {
	// 	int c1 = 121;
	// 	int c2 = 7;

	// 	printf("%d\n", ft_isprint(c1));
	// 	printf("%d\n", ft_isprint(c2));
	// 	return 0;
	// }