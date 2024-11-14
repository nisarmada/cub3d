/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 13:07:15 by nikos         #+#    #+#                 */
/*   Updated: 2023/10/28 00:43:11 by nikos         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}*/

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

// #include <stdio.h>
// int main ()
// {
//     char s[] = "yoo";
//     int fd1 = 1;
//     // int fd2 = 2;
//     // int fd3 = 5;

//     ft_putendl_fd(s, fd1);

//     // ft_putendl_fd(s, fd2);
//     // printf("\n");

//     // ft_putendl_fd(s, fd3);
//     // printf("\n");

// }