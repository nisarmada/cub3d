/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 16:50:02 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 16:34:21 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*int_ptr;
	size_t	i;

	int_ptr = (char *)ptr;
	i = 0;
	if (!ptr)
		return (NULL);
	while (i < num)
	{
		int_ptr[i] = value;
		i++;
	}
	return (ptr);
}

// int main()
// {
// 	int arr[42];
// 	int val = 42;
// 	size_t number = (sizeof(int) * val);
// 	ft_memset(arr, val, number);
// 	int i = 0;
// 	while (i < 42)
// 	{
// 		printf("%d\n", arr[i]);
// 		i++;
// 		printf("\n");
// 	}
// 	return(0);
// }
