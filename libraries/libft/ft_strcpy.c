#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

int ft_strcpy(char *src, char *dest, int j)
{
	int i;

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
