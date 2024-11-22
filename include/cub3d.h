/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:06:27 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/22 17:38:23 by elleneklund   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
# include <stddef.h>
# include <limits.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

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
#define TILE_SIZE 32

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

/*
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_player
{
	int		player_x;
	int		player_y;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		map_width;
	int		map_height;
}	t_map;

typedef struct s_ray
{
};
*/

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
	t_player	*player;
}	t_cub;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

void	parse_cub_file(char *filename, t_cub *cub);
t_cub	*initialize_cub(void);
int		valid_input(int ac, char **av);
void 	parse_redirections(char *line, t_cub *cub);
char *find_path(char *file);
void	parse_colors(char *line, t_cub *cub);
void	allocate_map(char *filename, t_cub *cub);
void map_parsing(char *line, t_cub *cub, int j);

/* inout_check */
char	*trim_spaces(char *str);

/* utils/extra */
char	*ft_strndup(const char *s1, size_t n);
int		is_whitespace(char file);
int		ft_isvalid_path_chars(int c);
int		ft_strcmp(const char *s1, const char *s2);

/* map parsing*/
int is_map_line(char *line);
void find_player_position(t_cub *cub);

/*rendering*/
int	render_game(t_cub *cub);
void draw_tile(mlx_image_t *img, int x, int y, int color);
void render_map(mlx_image_t *img, t_cub *cub);
void render_player(t_cub *cub, mlx_image_t *img);

#endif
