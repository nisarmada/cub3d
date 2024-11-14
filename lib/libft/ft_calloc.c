/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:42:19 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/27 23:49:59 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	real_size;
	void	*ptr;
	void	*fail;

	if (num == 0 || size == 0)
	{
		fail = malloc(1);
		if (!fail)
			return (NULL);
		return (fail);
	}
	real_size = num * size;
	if (real_size / size != num)
		return (NULL);
	real_size = num * size;
	ptr = malloc(real_size);
	if (real_size == 0 || ptr == NULL)
		return (NULL);
	ft_bzero(ptr, real_size);
	return (ptr);
}

// int main ()
// {
// 	int *arr1 = (int *)ft_calloc(5, sizeof(int));
// 	int *arr2 = (int *)calloc(5, sizeof(int));
// 	size_t	i = 0;

// 	while (i < 5)
// 	{
// 		printf("mine :%d\n", arr1[i]);
// 		printf("original :%d\n", arr2[i]);
// 		i++;
// 	}
// 	free(arr1);
// 	free(arr2);

// 	char *arr3 = (char *)ft_calloc(9, sizeof(char));
// 	char *arr4 = (char *)calloc(9, sizeof(char));

// 	strcpy(arr3, "yooo");
// 	strcpy(arr4, "yooo");
// 	printf("mine: %s\n", arr3);
// 	printf("orignal: %s", arr4);
// 	free(arr3);
// 	free(arr4);
// 	return 0;
// }