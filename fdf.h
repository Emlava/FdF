/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-21 14:55:30 by elara-va          #+#    #+#             */
/*   Updated: 2025-09-21 14:55:30 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define PI 3.14159265358979323846
# define MARGIN 150
# define SCALE 20
# define FALSE 0
# define TRUE 1
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

typedef struct s_minilibx_resources
{
	void	*mlx_ptr;
	void	*img_ptr;
	char	*img_addr;
	void	*win_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_minilibx_resources;

typedef struct s_map_resources
{
	int		fd;
	char	*gnl_str;
	char	**row;
	int		x;
	int		y;
	int		i;
}	t_map_resources;

typedef struct s_coordinates
{
	int						z;
	float					projected_x;
	float					projected_y;
	int						colour;
	struct s_coordinates	*next;
	struct s_coordinates	*prev;
}	t_coordinates;

typedef struct s_rendering_resources
{
	int	screen_width;
	int	screen_hight;
	int	row_length;
	int	nbr_of_rows;
	int	greatest_projected_x;
	int	greatest_projected_y;
	int	lowest_projected_x;
	int	lowest_projected_y;
	int	image_width;
	int	image_height;
}	t_rendering_resources;

typedef struct s_drawing_resources
{
	int		dx;
	int		dy;
	int		steps;
	float	slope_x;
	float	slope_y;
	float	r_gradient_rate;
	float	g_gradient_rate;
	float	b_gradient_rate;
}	t_drawing_resources;

/**** argument_check.c ****/
void	argument_check(int ac, char *av[]);

/**** manage_file_coordinates.c ****/
void	manage_file_coordinates(char *file, t_coordinates **coords,
			t_minilibx_resources *mlx_resources,
			t_rendering_resources *render_resources);

/**** manage_file_coordinates_utilities_1.c ****/
void	assign_various_resources(t_map_resources *map, t_coordinates **coords,
			t_minilibx_resources *mlx_resources,
			t_rendering_resources *render_resources);
int		check_for_valid_row_length(t_rendering_resources *render_resources,
			t_map_resources map);
int		create_next_node(t_coordinates **coords);
int		manage_colour(t_map_resources map, t_coordinates *coords);

/**** manage_file_coordinates_utilities_2.c ****/			
void	look_for_greatest_and_lowest_points(t_coordinates *coords,
			t_rendering_resources *render_resources);
int		adjust_coords_into_frame(t_coordinates *coords,
			t_rendering_resources *render_resources);
int		ishex(char *str);

/**** create_image.c ****/
void	create_image(t_minilibx_resources *mlx_resources,
			t_rendering_resources *render_resources, t_coordinates *coords);

/**** create_image_utilities.c ****/
void	initialize_mlx_resources(t_minilibx_resources *mlx_resources,
			t_rendering_resources render_resources, t_coordinates *coords);
void	get_colour_gradient_rates(int colour_1, int colour_2,
			t_drawing_resources *drawing_resources);
void	draw_pixel(t_minilibx_resources mlx_resources, t_coordinates *coord);
void	manage_colour_grading(int *colour,
			t_drawing_resources drawing_resources);
void	get_lower_coord(t_coordinates *coords, t_coordinates **lower_coord,
			t_rendering_resources render_resources);

/**** cleaning_utilities.c ****/
void	free_linked_list(t_coordinates *coord);
void	free_str_arr(char **str_arr);
void	mlx_clean_up(int instance, t_minilibx_resources mlx_resources);
void	clean_up_and_exit(int instance, ...);

/**** hooks.c ****/
int		manage_esc(int keycode, void *mlx_resources);
int		manage_cross(void *mlx_resources);

#endif
