/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:00:00 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/28 15:32:59 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void print_map(t_cub *cub)
{
	int i = 0;

	printf("printing map\n");
	while (cub->map[i])
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
	printf("max length %i\n", cub->map_width);
}
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
	// find_player_position(cub);
	// print_map(cub);
	// printf()
	if (!valid_map(cub, cub->map_height, cub->map_width))
		return (1); 
	printf("x->%i y->%i\n", cub->player->x, cub->player->y);
	render_game(cub);
	
	//printf("paths %s", cub->north);
	
}
