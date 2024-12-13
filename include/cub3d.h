/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/14 14:06:27 by eeklund       #+#    #+#                 */
/*   Updated: 2024/12/13 16:33:04 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
# include <stddef.h>
# include <limits.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WHITE 0xFFFFffFF
#define BLACK 0x000000FF
#define RED 0xFF0000FF
# define ORANGE 0xFFA500FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF
#define YELLOW 0xFFFF00FF
#define CYAN 0x00FFFFFF
#define MAGENTA 0xFF00FFFF
#define FLOOR_COLOR 0xDCE4E8FF  // Light blue-grey
#define CEILING_COLOR 0x4B4B4BFF  // Dark grey
#define WALL_COLOR 0x888888FF  // Light grey
#define INACCESSIBLE_COLOR 0x000000FF  // Black or grey
#define TILE_SIZE 32
#define MOVE_SPEED 2.5
#define ROTATION_SPEED 0.05

#define WIN_HEIGHT 600
#define WIN_WIDTH 800
#define	MINI_TILE 32 * 0.4
#define MINIMAP_SCALE 0.4
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10


typedef struct s_raycast
{
	float	distance;
	int		tile_x;
	int		tile_y;
}	t_raycast;

typedef struct s_key_value
{
	char	*key;
	char	*value;
}	t_key_value;

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
	float	angle;
	float	fov;
	int		changed;
}	t_player;

typedef enum e_wall_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_wall_direction ;

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
	bool	keys[256];
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
	int		floor_color;
	int		wall_color;
	int		map_width;
	int		map_height;
	int		dist_pplane;
	t_text	*text;
	mlx_t	*mlx;
	mlx_image_t	*img;
	t_player	*player;
}	t_cub;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// t_cub	*allocate_cub(void);
// void	parse_cub_file(char *filename, t_cub *cub);
t_cub	*initialize_cub(char *filename);
int		valid_input(int ac, char **av);
void 	parse_redirections(char *line, t_cub *cub);
void	parse_colors(char *line, t_cub *cub);
void	allocate_map(char *filename, t_cub *cub);
void	map_parsing(char *line, t_cub *cub, int j);
void	free_and_exit_game(t_cub *cub, int status);
t_cub	*init_parse_cub(char *filename);

/* inout_check */
char	*trim_spaces(char *str);

/* utils/extra */
char	*ft_strndup(const char *s1, size_t n);
int		is_whitespace(char file);
int		ft_isvalid_path_chars(int c);
int		ft_strcmp(const char *s1, const char *s2);


/* PARSING */

/* directions_parsing */
void parse_directions(char *line, t_cub *cub);

/* map parsing*/
int is_map_line(char *line);
// void find_player_position(t_cub *cub);
// void define_field_of_vision(t_cub *cub);
int valid_map(t_cub *cub, int height, int width);

/*rendering*/
void	init_mlx(t_cub *cub);
int	render_game(t_cub *cub);
void draw_tile(mlx_image_t *img, int x, int y, int color);
void render_map(mlx_image_t *img, t_cub *cub);
void render_player(t_cub *cub, mlx_image_t *img);
void render_fov(t_player *player, mlx_image_t *img, t_cub *cub);
void normalize_angle(float *angle);
void draw_line(t_player *player, mlx_image_t *img, int x, int y);
void draw_line_float(t_player *player, mlx_image_t *img, int x, int y);
void move_player(t_cub *cub, t_player *player, char direction);
void rotate_player(t_player *player, char direction);
void key_hook(mlx_key_data_t keycode, void *cub_ptr);
void hook_loop(void *cub_ptr);

/*prepare game */
void	render_frame(t_cub *cub);

/*raycasting*/
void	render_3D_view(t_cub *cub, t_player *player);
float	cast_single_ray(t_cub *cub, t_player *player, float ray_angle, float *wall_hit_position, t_wall_direction *wall_direction);

/* 3D_rendering */
void	render_wallslice(t_cub *cub, float dist, int x, float wall_hit_position, t_wall_direction wall_direction);
int 	get_texture_color(t_cub *cub, int text_x, int text_y, mlx_texture_t *texture, t_wall_direction wall_direction);
void	print_map(t_cub *cub);
void	render_floor_ceiling(t_cub *cub);

#endif
