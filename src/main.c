/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:00:00 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/14 16:06:32 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	char *filename;
	t_cub	*cub;

	(void)ac;
	cub = initialize_cub();
	filename = av[1];
	parse_cub_file(filename, cub);
	//input check
	//parsing of map
	// rendering?
	// "playing"
}