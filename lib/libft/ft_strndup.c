#include "libft.h"

char *strndup(const char *s, size_t n)
{
    char *result;
    size_t len = ft_strlen(s);

    if (len > n)
        len = n;

    result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    ft_memcpy(result, s, len);
    result[len] = '\0';

    return result;
}