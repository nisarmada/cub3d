/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:56:47 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 14:00:15 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*#include<stdio.h>
int main ()
{
    char str[] = "";
    ft_isalpha(str);
    printf("%d", ft_isalpha(str));
    return 0;
}*/