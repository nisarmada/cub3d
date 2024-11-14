/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 12:13:35 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 13:38:05 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	unsigned char	*byte_ptr;
	size_t			i;

	i = 0;
	byte_ptr = (unsigned char *)ptr;
	while (i < n)
	{
		byte_ptr[i] = 0;
		i++;
	}
}

/*int main()
{
	int arr[4];
	int i = 0;
	size_t	number = sizeof(arr);

	ft_bzero(arr, number);
	while (i < 4)
	{
		printf("%d\n", arr[i]);
		i++;
	}
	return 0;
}*/