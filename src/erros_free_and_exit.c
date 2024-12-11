/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   erros_free_and_exit.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: elleneklund <elleneklund@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 14:12:13 by elleneklund   #+#    #+#                 */
/*   Updated: 2024/12/11 14:26:01 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free (map);
}
void	delete_text_img(mlx_t *mlx, t_text *texture)
{
	mlx_delete_image(mlx, texture->ea_img);
	mlx_delete_image(mlx, texture->we_img);
	mlx_delete_image(mlx, texture->so_img);
	mlx_delete_image(mlx, texture->no_img);
}

void	free_textures(t_text *texture)
{
	mlx_delete_texture(texture->ea);
	mlx_delete_texture(texture->we);
	mlx_delete_texture(texture->so);
	mlx_delete_texture(texture->no);
}

void	free_and_exit_game(t_cub *cub, int status)
{
	if (cub->img)
		mlx_delete_image(cub->mlx, cub->img);
	delete_text_img(cub->mlx, cub->text);
	free_textures(cub->text);
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	free(cub->player);
	free_map(cub->map);
	// implent error msg system
	if (status == 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}