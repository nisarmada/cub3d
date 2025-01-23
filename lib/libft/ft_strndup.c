/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 14:49:14 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/23 14:50:17 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s, len);
	result[len] = '\0';
	return (result);
}
