/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 18:26:55 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/04/16 17:26:12 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(const char *str, const char *buffer)
{
	size_t	i;
	size_t	n;
	char	*ptr;

	i = 0;
	n = 0;
	ptr = (char *)malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
	if (!ptr)
		return (free_secure(&ptr));
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	while (buffer[n] != '\0')
	{
		ptr[i + n] = buffer[n];
		n++;
	}
	ptr[i + n] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *str, char *buffer)
{
	char	*ptr;

	if (!str)
	{
		free(str);
		str = (char *)malloc(1);
		str[0] = '\0';
	}
	if (!buffer)
		return (free_secure(&buffer));
	ptr = ft_strconcat(str, buffer);
	free_secure(&str);
	return (ptr);
}
// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t		tot_len;
// 	size_t		i;
// 	size_t		n;
// 	char		*ptr;

// 	tot_len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	i = 0;
// 	n = 0;
// 	ptr = (char *)malloc(sizeof(char) * tot_len);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[n] != '\0')
// 	{
// 		ptr[i] = s2[n];
// 		i++;
// 		n++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }
