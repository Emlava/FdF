/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-20 17:33:04 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-20 17:33:04 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_coordinates coord_1, t_coordinates coord_2,
			t_minilibx_resources mlx_resources)
{
	t_drawing_resources	drawing_resources;

	drawing_resources.dx = coord_2.projected_x - coord_1.projected_x;
	drawing_resources.dy = coord_2.projected_y - coord_1.projected_y;
	if (ft_abs(drawing_resources.dx) > ft_abs(drawing_resources.dy))
		drawing_resources.steps = ft_abs(drawing_resources.dx);
	else
		drawing_resources.steps = ft_abs(drawing_resources.dy);
	drawing_resources.slope_x
		= (float)drawing_resources.dx / (float)drawing_resources.steps;
	drawing_resources.slope_y
		= (float)drawing_resources.dy / (float)drawing_resources.steps;
	if (coord_1.colour != coord_2.colour)
		get_colour_gradient_rates(coord_1.colour, coord_2.colour,
			&drawing_resources);
	while (drawing_resources.steps)
	{
		draw_pixel(mlx_resources, &coord_1);
		coord_1.projected_x += drawing_resources.slope_x;
		coord_1.projected_y += drawing_resources.slope_y;
		if (coord_1.colour != coord_2.colour)
			manage_colour_grading(&coord_1.colour, drawing_resources);
		drawing_resources.steps--;
	}
	return ;
}

static void	draw_rows(t_coordinates *coords,
	t_rendering_resources render_resources, t_minilibx_resources mlx_resources)
{
	int	lines_in_row;
	int	lines_to_draw;

	lines_in_row = render_resources.row_length - 1;
	lines_to_draw = lines_in_row;
	while (1)
	{
		if (lines_to_draw)
		{
			draw_line(*coords, *coords->next, mlx_resources);
			lines_to_draw--;
		}
		else
			lines_to_draw = lines_in_row;
		coords = coords->next;
		if (coords->next == NULL)
		{
			draw_pixel(mlx_resources, coords);
			return ;
		}
	}
}

static void	draw_columns(t_coordinates *coords,
	t_rendering_resources render_resources, t_minilibx_resources mlx_resources)
{
	t_coordinates	*upper_coord;
	t_coordinates	*lower_coord;

	upper_coord = coords;
	get_lower_coord(coords, &lower_coord, render_resources);
	while (1)
	{
		draw_line(*upper_coord, *lower_coord, mlx_resources);
		if (lower_coord->next == NULL)
		{
			draw_pixel(mlx_resources, lower_coord);
			return ;
		}
		upper_coord = upper_coord->next;
		lower_coord = lower_coord->next;
	}
}

static void	draw_image(t_coordinates *coords,
	t_rendering_resources render_resources, t_minilibx_resources mlx_resources)
{
	if (render_resources.nbr_of_rows == 1 && render_resources.row_length == 1)
		draw_pixel(mlx_resources, coords);
	else
	{
		if (render_resources.row_length > 1)
			draw_rows(coords, render_resources, mlx_resources);
		if (render_resources.nbr_of_rows > 1)
			draw_columns(coords, render_resources, mlx_resources);
	}
	return ;
}

void	create_image(t_minilibx_resources *mlx_resources,
	t_rendering_resources *render_resources, t_coordinates *coords)
{
	initialize_mlx_resources(mlx_resources, *render_resources, coords);
	draw_image(coords, *render_resources, *mlx_resources);
	free_linked_list(coords);
	return ;
}
