/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:06:27 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/14 16:34:12 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define CYAN 0x00FFFF
#define MAGENTA 0xFF00FF
#define FLOOR_COLOR 0xDCE4E8  // Light blue-grey
#define CEILING_COLOR 0x4B4B4B  // Dark grey
#define WALL_COLOR 0x888888  // Light grey
#define INACCESSIBLE_COLOR 0x000000  // Black or grey

typedef struct s_cub
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
	int		floor_color;
	int		wall_color;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_orientation;
}	t_cub;

void	parse_cub_file(char *filename, t_cub *cub);
t_cub	*initialize_cub(void);
#endif
