/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:05:38 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 14:02:00 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int main()
// {
// 	char str1[] = "342354";
// 	char str2[] = "";
// 	char str3[] = "329487f";
// 	char str4[] = "234 435";
// 	printf("%d\n", ft_isdigit(str1));
// 	printf("%d\n", ft_isdigit(str2));
// 	printf("%d\n", ft_isdigit(str3));
// 	printf("%d\n", ft_isdigit(str4));
// 	return 0;
// } 