/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nikos <nikos@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 11:05:41 by nikos         #+#    #+#                 */
/*   Updated: 2024/03/01 18:45:45 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

void	smth(unsigned int i, char *c)
{
	*c = *c + i;
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(s);
	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}

// int main ()
// {
//     char s[] = "hello";
//     ft_striteri(s, smth);
//     printf("%s", s);
//     return 0;
// }