/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 14:51:47 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 14:52:03 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

int	ft_strcpy(char *src, char *dest, int j)
{
	int	i;

	i = 0;
	if (!src)
		return (j);
	while (src[i])
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	return (j);
}
