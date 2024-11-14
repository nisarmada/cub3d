/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 18:06:30 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/18 18:24:31 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	steps(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;
	long	num;
	int		length;

	num = n;
	i = 0;
	length = steps(num);
	res = malloc(length + 1);
	if (!res)
		return (NULL);
	if (num == 0)
		res[0] = '0';
	if (num < 0)
		num = -num;
	while (num > 0)
	{
		res[length - 1 - i] = ((num % 10) + '0');
		i++;
		num /= 10;
	}
	if (n < 0)
		res[0] = '-';
	res[length] = '\0';
	return (res);
}

// int main ()
// {
// 	int n = -345;
// 	char *d = ft_itoa(n);
// 	printf("%s", d);

// 	return 0;
// }