/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 16:40:34 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/05/17 17:19:10 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			src_len;
	size_t			i;
	char			*d;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (len == 0 || start >= src_len)
		return (ft_strdup(""));
	if (start + len > src_len)
		len = src_len - start;
	d = malloc(sizeof(char) * (len + 1));
	if (d == NULL)
		return (NULL);
	i = 0;
	while ((i < len) && (i + start <= src_len))
	{
		d[i] = ((char *)s)[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
