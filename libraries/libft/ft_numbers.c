/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numbers.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 17:02:01 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/04/01 13:51:28 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	ft_putnbr(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		counter += ft_putchar('-');
		n = -n;
	}
	if (n / 10 != 0)
	{
		counter += ft_putnbr(n / 10);
	}
	counter += ft_putchar(n % 10 + '0');
	return (counter);
}

int	ft_uns_putnbr(unsigned int n)
{
	int	counter;

	counter = 0;
	if (n >= 10)
	{
		counter += ft_putnbr(n / 10);
	}
	counter += ft_putchar(n % 10 + '0');
	return (counter);
}

int	putnbr_base(unsigned int nbr, char *base)
{
	int		len;
	long	nb;
	int		counter;

	len = ft_strlen(base);
	nb = nbr;
	counter = 0;
	if (nb < len)
	{
		ft_putchar(base[nb]);
		counter++;
	}
	if (nb >= len)
	{
		counter += putnbr_base(nb / len, base);
		counter += putnbr_base(nb % len, base);
	}
	return (counter);
}

int	hex_address(void *ptr, char *base)
{
	char			buffer[20];
	unsigned long	address;
	int				length;
	int				counter;

	length = 0;
	address = (unsigned long)ptr;
	if (!address)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	while (address > 0)
	{
		buffer[length++] = base[address % 16];
		address /= 16;
	}
	ft_putstr("0x");
	counter = length + 2;
	while (length > 0)
	{
		write(1, &buffer[length - 1], 1);
		length--;
	}
	return (counter);
}
