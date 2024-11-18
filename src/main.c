/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:00:00 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/18 20:17:44 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	char	*filename;
	t_cub	*cub;

	filename = av[1];
	(void)ac;
	if (!valid_input(ac, av))
		return (1);
	printf("input file is valid \n");
	cub = initialize_cub();
	parse_cub_file(filename, cub);
	printf("paths %s", cub->north);
}
