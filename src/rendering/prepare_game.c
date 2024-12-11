/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_game.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/21 14:14:42 by nsarmada      #+#    #+#                 */
/*   Updated: 2024/12/11 11:48:10 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_cub *cub)
{
	render_3D_view(cub, cub->player);
	render_map(cub->img, cub);
	render_player(cub, cub->img);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
}

int	load_textures(t_cub *cub)
{
	// printf("path: %s\n", cub->north);
	// printf("path: %s\n", cub->south);
	// printf("path: %s\n", cub->west);
	// printf("path: %s\n", cub->east);

	cub->text->no = mlx_load_png(cub->north);
	cub->text->so = mlx_load_png(cub->south);
	cub->text->we = mlx_load_png(cub->west);
	cub->text->ea = mlx_load_png(cub->east);
	if (!cub->text->no || !cub->text->so || !cub->text->we || !cub->text->ea)						
	{
		printf("Failed to load XPM file.\n");
		return (0);
	}
	cub->text->no_img = mlx_texture_to_image(cub->mlx, cub->text->no);
	cub->text->so_img = mlx_texture_to_image(cub->mlx, cub->text->so);
	cub->text->we_img = mlx_texture_to_image(cub->mlx, cub->text->we);
	cub->text->ea_img = mlx_texture_to_image(cub->mlx, cub->text->ea);
	if (!cub->text->no_img || !cub->text->so_img || !cub->text->we_img || !cub->text->ea_img)
	{
		printf("Failed to convert PNG texture to image.\n");
		return (0);
	}
	return (1);
}

int	render_game(t_cub *cub)
{
	//void	*mlx;
	//mlx_image_t *img;

	cub->mlx = mlx_init(800, 600, "Cub3d", true);
	if (!cub->mlx)
		return (1);
	cub->img = mlx_new_image(cub->mlx, 800, 600);
	if (!cub->img)
		return (1);
	if (!load_textures(cub))
		return (1);
	render_frame(cub);
	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_loop_hook(cub->mlx, hook_loop, cub);
	mlx_loop(cub->mlx);
	return (0);
}
