/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsarmada <nsarmada@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 17:43:15 by nsarmada      #+#    #+#                 */
/*   Updated: 2023/10/13 15:24:32 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar('-', fd);
		ft_putchar('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar(n % 10 + '0', fd);
}

// int main()
// {
// 	int nbr = -2147483648;
// 	ft_putnbr_fd(nbr, 1);
// 	return 0;
// }