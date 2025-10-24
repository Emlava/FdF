/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_image_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-20 18:47:25 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-20 18:47:25 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	initialize_mlx_resources(t_minilibx_resources *mlx_resources,
	t_rendering_resources render_resources, t_coordinates *coords)
{
	mlx_resources->img_ptr = mlx_new_image(mlx_resources->mlx_ptr, render_resources.largest_projected_x + WINDOW_MARGIN,
		render_resources.largest_projected_y + WINDOW_MARGIN);
	if (!mlx_resources->img_ptr)
		clean_up_and_exit(5, *mlx_resources, coords); // Instance 5, free mlx_ptr and coords
	mlx_resources->img_addr = mlx_get_data_addr(mlx_resources->img_ptr,
		&mlx_resources->bits_per_pixel, &mlx_resources->size_line, &mlx_resources->endian);
	if (!mlx_resources->img_addr)
		clean_up_and_exit(6, *mlx_resources, coords); // Instance 6, free mlx_ptr and coords, destroy image
	return ;
}

static int	manage_colour(int colour_1, int colour_2)
{
	int		colour_difference;
	int	colour_gradient_rate;

	colour_gradient_rate = 0;
	if (colour_1 != colour_2)
	{
		colour_difference = colour_1 - colour_2;
		colour_gradient_rate = roundf((float)colour_difference / SCALE);
	}
	return (colour_gradient_rate);
}

static void	draw_pixel_in_line(t_minilibx_resources mlx_resources, t_coordinates *coord_1,
	t_coordinates coord_2, t_drawing_resources drawing_resources)
{
	int		row;
	int		column;
	char	*dest;

	if (coord_1->already_drawn)
		return ;
	row = coord_1->projected_y * mlx_resources.size_line;
	column = coord_1->projected_x * (mlx_resources.bits_per_pixel / 8);
	dest = mlx_resources.img_addr + row + column;
	if (drawing_resources.i != 0)
		coord_1->colour += drawing_resources.colour_gradient_rate;
	if (coord_1->colour < coord_2.colour)
		*(int*)dest = coord_1->colour;
	else
		*(int*)dest = coord_2.colour;
	coord_1->already_drawn = YES;
	return ;
}

void	draw_line(t_coordinates coord_1, t_coordinates coord_2, t_minilibx_resources mlx_resources)
{
	t_drawing_resources	drawing_resources;

	drawing_resources.dx = coord_2.projected_x - coord_1.projected_x;
	drawing_resources.dy = coord_2.projected_y - coord_1.projected_y;
	if (drawing_resources.dx > drawing_resources.dy)
		drawing_resources.steps = drawing_resources.dx;
	else
		drawing_resources.steps = drawing_resources.dy;
	drawing_resources.slope_x = drawing_resources.dx / (float)drawing_resources.steps;
	drawing_resources.slope_y = drawing_resources.dy / (float)drawing_resources.steps;
	drawing_resources.colour_gradient_rate = manage_colour(coord_1.colour, coord_2.colour);
	drawing_resources.i = 0;
	while (drawing_resources.i <= drawing_resources.steps)
	{
		draw_pixel_in_line(mlx_resources, &coord_1, coord_2, drawing_resources);
		coord_1.projected_x += drawing_resources.slope_x;
		coord_1.projected_y += drawing_resources.slope_y;
		drawing_resources.i++;
	}
	return ;
}

void	get_lower_coord(t_coordinates *coords, t_coordinates **lower_coord,
	t_rendering_resources render_resources)
{
	int	coord_nbr;

	*lower_coord = coords;
	coord_nbr = 1;
	while (coord_nbr <= render_resources.row_length) // && (*lower_coord)->next != NULL
	{
		*lower_coord = (*lower_coord)->next;
		coord_nbr++;
	}
	return ;
}
