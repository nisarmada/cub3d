/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3D_rendering.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eeklund <eeklund@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/28 16:34:35 by eeklund       #+#    #+#                 */
/*   Updated: 2024/11/29 14:05:42 by eeklund       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


typedef  struct  s_line
{
	int  x; //the x coordinate of line relative to screen
	int  y; //the current pixel index of the line (along y axis)
	int  y0; //y start index of drawing texture
	int  y1; //y end index of drawing texture
	int  tex_x; //x coordinate of texture to draw
	int  tex_y; //y coordinate of texture to draw
} t_line;

// correct_dist = distorted_dist * cos(angle_from distorted ray to middle_ray) because: cos(b) = correct_dist/distorted_dist
// (30 degrees for the leftmost ray and -30 degrees for the right most ray)


// walls are 90° angle to the floor
// cube size =  32*32*32 (in ex 64*64*64 is used)(for now) good with a number divided by 2; because we can perform some arithmetic shift operations on such number (shift operations are faster than multiplication or division).
// player_fov = 60° 
// player_height = cube-unit / 2 = 16 units
//
int	distance_to_wall()
{
	
}