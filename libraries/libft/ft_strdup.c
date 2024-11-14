/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:28:23 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/03/01 18:47:06 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	d = malloc(len + 1);
	if (d == NULL)
		return (NULL);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

// int main()
// {
// 	const char *s1 = "yooo";
// 	char *d1 = ft_strdup(s1);
// 	char *d2 = strdup(s1);
// 	printf("mine :%s\n", d1);
// 	printf("original: %s\n", d2);
// 	free(d1);
// 	free(d2);
// 	return 0;
// }