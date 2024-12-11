/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 13:00:00 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/11 13:15:56 by elleneklund   ########   odam.nl         */
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
	if (!valid_input(ac, av))
		return (1);
	cub = initialize_cub(filename);
	if (!cub)
		return (1);
	// parse_cub_file(filename, cub);
	// print_map(cub);
	if (!valid_map(cub, cub->map_height, cub->map_width))
		return (1); 
	render_game(cub);
	mlx_terminate(cub->mlx);
}
void	free_and_exit(t_cub *cub, int status)
{
	if (cub->img)
		mlx_delete_image(cub->mlx, cub->img);
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	if (status == 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}