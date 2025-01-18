/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors_free_and_exit.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 14:12:13 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/18 18:19:55 by nikos         ########   odam.nl         */
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
	if (status == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	free_cub(t_cub *cub)
{
	free(cub->player);
	free(cub->text);
	if (cub->map)
		free_map(cub->map);
	free(cub->east);
	free(cub->north);
	free(cub->west);
	free(cub->south);
	free(cub);
}