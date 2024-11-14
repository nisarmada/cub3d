/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:00:00 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/14 16:56:14 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{

	int i;

	i = ft_strlen("HEEEL");
	printf("int i %i\n", i);
	if (!valid_input(ac, av))
		return (1);
	//parsing of map
	// rendering?
	// "playing"
}
