/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 11:28:53 by eeklund       #+#    #+#                 */
/*   Updated: 2025/01/23 14:48:26 by nsarmada      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

# define FLOOR_COLOR 0xDCE4E8FF
# define CEILING_COLOR 0x4B4B4BFF
# define WALL_COLOR 0x888888FF
# define INACCESSIBLE_COLOR 0x000000FF

// #define TILE_SIZE 32
# define MOVE_SPEED 2.5
# define ROTATION_SPEED 0.05

typedef struct s_raycast
{
	float	distance;
	int		tile_x;
	int		tile_y;
}	t_raycast;

typedef struct s_coord
{
	float	x;
	float	y;
}	t_coord;

typedef struct s_slice
{
	int		y; //the current pixel index of the line (along y axis)
	int		start_y; //y start index of drawing texture
	int		end_y; //y end index of drawing texture
	int		color;
	float	step;
	float	text_pos;
}	t_slice;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef enum e_wall_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_direction;

typedef struct s_raycasting
{
	float				ray_angle;
	float				wall_hit_position;
	t_wall_direction	wall_direction;
	float				distorted_distance;
	float				correct_dist;
	int					x; // For render_wallslice
	float				line_height; // For render_wallslice
	int					text_x; // For render_wallslice
	int					text_y; // For render_wallslice
}	t_raycasting;

typedef struct s_render_context
{
	float		scale;
	mlx_image_t	*img;
}	t_render_context;

typedef struct s_ray
{
	float	ray_x; // starting position x
	float	ray_y; // starting poisition y
	float	dir_x; // direction in x axis
	float	dir_y; // direction in y axis
	int		tile_x; // tile normalization
	int		tile_y;
	int		step_x; // determine if we're moving in x or y axis
	int		step_y;
	float	delta_x; // differential with respect to x
	float	delta_y;
	float	distance_x; //distance to next vertical border
	float	distance_y; // d3istance to next horizontal border
}	t_ray;

/* RENDERING */

/*prepare game */
void	render_frame(t_cub *cub);

/*draw minimap*/
void	draw_tile(mlx_image_t *img, t_coord *tile, float scale, int color);
float	render_map(mlx_image_t *img, t_cub *cub);

/*draw miniplayer*/
float	calculate_scale(int map_width, int map_height, mlx_image_t *img);
void	render_player(t_cub *cub, mlx_image_t *img, float scale);
void	render_fov(t_player *player, t_cub *cub, float scale);

/*HOOKS*/
void	key_hook(mlx_key_data_t keycode, void *cub_ptr);
void	hook_loop(void *cub_ptr);
void	resize_callback(int32_t width, int32_t height, void *param);

/*draw line*/
void	init_line_1(t_line *line, t_cub *cub, float scale);
void	init_line_2(t_line *line, int dest_x, int dest_y);
void	init_line_direction(t_line *line);
void	draw_line_pixel(t_line *line, t_cub *cub);
void	update_line_position(t_line *line);

/*player_movement*/
void	move_player(t_cub *cub, t_player *player, char direction);
void	rotate_player(t_player *player, char direction);

/*extras*/
void	normalize_angle(float *angle);
void	draw_line(t_cub *cub, int x, int y, float scale);

/*raycasting*/
void	render_view(t_cub *cub, t_player *player);
float	cast_single_ray(t_cub *cub, t_raycasting *rc);
float	calc_ray_distance(float x1, float y1, float x2, float y2);

/*raycasting_helper*/
void	handle_vertical_hit(t_ray *r, t_raycasting *rc);
bool	check_wall_collision(t_cub *cub, t_ray *r);
float	process_ray_hit(t_cub *cub, t_ray *r,
			t_raycasting *rc, bool is_horizontal);
void	handle_horizontal_hit(t_ray *r, t_raycasting *rc);

/* 3D_rendering */
void	render_wallslice(t_cub *cub, t_raycasting *rc);
int		get_texture_color(t_cub *cub, mlx_texture_t *texture, t_raycasting *rc);
void	print_map(t_cub *cub);
void	render_floor_ceiling(t_cub *cub);

void	free_and_exit_game(t_cub *cub, int status);

#endif