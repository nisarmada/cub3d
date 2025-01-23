/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:06:27 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/23 15:30:14 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <limits.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif

# define GREEN 0x00FF00FF

# define TILE_SIZE 32

# define WIN_HEIGHT 600
# define WIN_WIDTH 800
# define MINIMAP_SCALE 0.4
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define MINI_HEIGHT 200
# define MINI_WIDTH 200

typedef struct s_player
{
	float	x;
	float	y;
	char	orientation;
	float	angle;
	float	fov;
	int		changed;
}	t_player;

typedef struct s_text
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_image_t		*no_img;
	mlx_image_t		*so_img;
	mlx_image_t		*we_img;
	mlx_image_t		*ea_img;
	uint32_t		*no_pixels; // Pixel data for North texture
	uint32_t		*so_pixels; // Pixel data for South texture
	uint32_t		*we_pixels; // Pixel data for West texture
	uint32_t		*ea_pixels;
}	t_text;

typedef struct s_cub
{
	bool		keys[512];
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**map;
	int			floor_color;
	int			wall_color;
	int			map_width;
	int			map_height;
	int			win_width;
	int			win_height;
	int			dist_pplane;
	bool		first_render;
	t_text		*text;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
}	t_cub;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
	uint8_t		alpha;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
}	t_rgb;

void	print_map(t_cub *cub);

/* INPUT */
int		valid_input(int ac, char **av); //I main
int		error_msg(char *msg, int status);
int		error_msg_spec(char *msg, void *spec, int status);

/* PARSING */
void	finish_file(int fd);
t_cub	*init_cub(char *filename); //i main
int		is_map_line(char *line);
void	parse_directions(char *line, t_cub *cub);
int		valid_map(t_cub *cub, int height, int width); //i main
void	allocate_map(char *filename, t_cub *cub);
void	map_parsing(char *line, t_cub *cub, int j);
void	parse_colors(char *line, t_cub *cub);
int		valid_map_row(t_cub	*cub, int row);

/* RENDERING */
int		render_game(t_cub *cub); //i main

/* UTILS/extra */
char	*ft_strndup(const char *s1, size_t n);
int		is_whitespace(char file);
int		ft_isvalid_path_chars(int c);
int		ft_strcmp(const char *s1, const char *s2);

/* FREE AND EXIT */
void	free_cub(t_cub *cub); //i main

#endif
