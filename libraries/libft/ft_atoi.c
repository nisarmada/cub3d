/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 19:24:39 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/05/17 17:19:37 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long	ft_atoi(const char *nptr)
{
	int		i;
	long	sum;
	int		sign;

	i = 0;
	sign = 1;
	sum = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else
		if (nptr[i] == '+')
			i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	return (sum * sign);
}
