/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:00:00 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/27 19:22:02 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void print_map(t_cub *cub)
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
	if (!valid_map(cub, cub->map_height, cub->map_width))
		return (1); 
	// find_player_position(cub);
	printf("x->%i y->%i\n", cub->player->x, cub->player->y);
	render_game(cub);
	//printf("paths %s", cub->north);
	
	print_map(cub);
}
