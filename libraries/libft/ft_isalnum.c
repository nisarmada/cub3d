/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:15:01 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:38:24 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}

/*int main()
{
	int c1 = 5;
	int c2 = 'b';
	int c3 = 'D';

	printf("%d\n", ft_isalnum(c1));
	printf("%d\n", ft_isalnum(c2));
	printf("%d\n", ft_isalnum(c3));
	return 0;


}*/