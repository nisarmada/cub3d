/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 13:01:37 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/04/01 13:51:41 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <inttypes.h>
#include <stdio.h>
#include "libft.h"
#include <limits.h>

int	help(const char format, va_list	args)
{
	int	counter;

	counter = 0;
	if (format == '%')
		counter += ft_putchar('%');
	else if (format == 'c')
		counter += ft_putchar(va_arg(args, int));
	else if (format == 's')
		counter += ft_putstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		counter += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		counter += ft_uns_putnbr(va_arg(args, unsigned int));
	else if (format == 'p')
		counter += hex_address(va_arg(args, void *), "0123456789abcdef");
	else if (format == 'x')
		counter += putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		counter += putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	else
		counter += ft_putchar('%');
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counter;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	counter = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				counter += help(*format, args);
			else
			{
				va_end(args);
				return (-1);
			}
		}
		else
			counter += ft_putchar(*format);
		format++;
	}
	return (counter);
}
