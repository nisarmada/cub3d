/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 19:03:23 by elleneklund   #+#    #+#                 */
/*   Updated: 2025/01/20 11:56:23 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

void	key_hook(mlx_key_data_t keycode, void *cub_ptr)
{
	t_cub		*cub;
	const int	max_keys = sizeof(cub->keys) / sizeof(cub->keys[0]);

	cub = (t_cub *)cub_ptr;
	if (keycode.key >= 0 && keycode.key < max_keys)
	{
		if (keycode.action == MLX_PRESS)
			cub->keys[keycode.key] = true;
		else if (keycode.action == MLX_RELEASE)
			cub->keys[keycode.key] = false;
	}
	if (keycode.key == MLX_KEY_ESCAPE && keycode.action == MLX_RELEASE)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
		exit(EXIT_SUCCESS);
	}
}

void	hook_loop(void *cub_ptr)
{
	t_cub	*cub;

	cub = (t_cub *)cub_ptr;
	if (cub->keys[MLX_KEY_W])
		move_player(cub, cub->player, 'W');
	if (cub->keys[MLX_KEY_S])
		move_player(cub, cub->player, 'S');
	if (cub->keys[MLX_KEY_A])
		move_player(cub, cub->player, 'A');
	if (cub->keys[MLX_KEY_D])
		move_player(cub, cub->player, 'D');
	if (cub->keys[MLX_KEY_LEFT])
		rotate_player(cub->player, 'L');
	if (cub->keys[MLX_KEY_RIGHT])
		rotate_player(cub->player, 'R');
	if (cub->player->changed == 1)
	{
		render_frame(cub);
		cub->player->changed = 0;
	}
}

void	reset_width_height(t_cub *cub, int32_t width, int32_t height)
{
	if (width < 200)
		width = 200;
	if (height < 200)
		height = 200;
	cub->win_width = width;
	cub->win_height = height;
}

void	resize_callback(int32_t width, int32_t height, void *param)
{
	t_cub	*cub;
	float	scale;

	cub = (t_cub *)param;
	if (cub->img)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = NULL;
	}
	reset_width_height(cub, width, height);
	cub->img = mlx_new_image(cub->mlx, cub->win_width, cub->win_height);
	if (!cub->img)
		free_and_exit_game(cub, EXIT_FAILURE);
	cub->dist_pplane = ((cub->win_width / 2) / tan(0.524));
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0)
		free_and_exit_game(cub, EXIT_FAILURE);
	ft_memset(cub->img->pixels, 0,
		cub->img->width * cub->img->height * sizeof(int32_t));
	render_view(cub, cub->player);
	scale = render_map(cub->img, cub);
	render_player(cub, cub->img, scale);
}
