/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 15:54:20 by nsarmada      #+#    #+#                 */
/*   Updated: 2025/01/06 14:36:29 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_cub	*allocate_cub(void)
{
	t_cub *cub;

	cub = malloc(sizeof(t_cub));
    if (!cub)
        return (NULL);
    // Allocate memory for player
    cub->player = malloc(sizeof(t_player));
    if (!cub->player)
    {
        // If player allocation fails, free cub and return NULL
        free(cub);
        return (NULL);
    }
	cub->player->orientation = '\0';
	cub->text = malloc(sizeof(t_text));
	if (!cub->text)
	{
		free(cub->player);
		free(cub);
		return (NULL);
	}
	cub->map_width = 0;
	return (cub);
}

static void parse_cub_file(char *filename, t_cub *cub)
{
	int		fd;
	char	*line;
	int		j;

	j = 0;
	(void)cub;
	allocate_map(filename, cub);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		// line = trim_spaces(line); // ellen added this line
		parse_directions(line, cub);
		parse_colors(line, cub);
		if (is_map_line(line))
			break;
		line = get_next_line(fd);
	}
	while (line)
	{
		map_parsing(line, cub, j);
		j++;
		line = get_next_line(fd);
	}
	cub->map[j] = NULL;
	close(fd);
}

t_cub	*init_parse_cub(char *filename)
{
	t_cub	*cub;
	int		i;

    // Allocate memory for cub
	cub = allocate_cub();
	parse_cub_file(filename, cub);
	cub->player->changed = 0;
	cub->dist_pplane = ((WIN_WIDTH / 2 ) / tan(0.524));
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	//distance from player to projection plan = (projectionplan width / 2) / tan(30 (half of fov)) --> 692
	// printf("dist: %i\n", cub->dist_pplane);
	i = 0;
	while (i < 256)
	{
		cub->keys[i] = false;
		i++;
	}
	return (cub);
}

// t_cub *initialize_cub(char *filename)
// {
// 	t_cub *cub;

//     // Allocate memory for cub
// 	cub = allocate_cub();
// 	parse_cub_file(filename, cub);
//     // cub = malloc(sizeof(t_cub));
//     // if (!cub)
//     //     return (NULL);

//     // // Allocate memory for player
//     // cub->player = malloc(sizeof(t_player));
//     // if (!cub->player)
//     // {
//     //     // If player allocation fails, free cub and return NULL
//     //     free(cub);
//     //     return (NULL);
//     // }
// 	// cub->text = malloc(sizeof(t_text));
// 	// if (!cub->text)
// 	// {
// 	// 	free(cub->player);
// 	// 	free(cub);
// 	// 	return (NULL);
// 	// }
// 	// cub->text->no = NULL;
// 	// cub->text->so = NULL;
// 	// cub->text->we = NULL;
// 	// cub->text->ea = NULL;
// 	// cub->text->no_img = NULL;
// 	// cub->text->we_img = NULL;
// 	// cub->text->so_img = NULL;
// 	// cub->text->ea_img = NULL;
//     // // Initialize player fields to 0 or default values
//     // cub->player->x = 0;
//     // cub->player->y = 0;
//     // cub->player->angle = 0;
//     // cub->player->fov = 0;
//     // cub->player->orientation = '\0';
// 	cub->player->changed = 0;

//     // Initialize other fields
//     // cub->east = NULL;
//     // cub->west = NULL;
//     // cub->north = NULL;
//     // cub->south = NULL;
//     // cub->map = NULL;
//     // cub->mlx = NULL;
//     // cub->img = NULL;
// 	// cub->text = NULL;
// 	cub->dist_pplane = 692;
// 	for (int i = 0; i < 256; i++)
// 		cub->keys[i] = false;
// 	return (cub);
// }

// void find_player_position(t_cub *cub)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (cub->map[j])
// 	{
// 		i = 0;
// 		while (cub->map[j][i])
// 		{
// 			if (cub->map[j][i] == 'N' || cub->map[j][i] == 'S'
// 				|| cub->map[j][i] == 'W' || cub->map[j][i] == 'E')
// 			{
// 				cub->player->x = i * TILE_SIZE + TILE_SIZE / 2;
// 				cub->player->y = j * TILE_SIZE + TILE_SIZE / 2;
// 				cub->player->orientation = cub->map[j][i];
// 				define_field_of_vision(cub);
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// }
