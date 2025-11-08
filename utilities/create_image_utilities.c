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
	mlx_resources->img_ptr = mlx_new_image(mlx_resources->mlx_ptr,
			render_resources.image_width, render_resources.image_height);
	if (!mlx_resources->img_ptr)
		clean_up_and_exit(5, mlx_resources, coords);
	mlx_resources->img_addr = mlx_get_data_addr(mlx_resources->img_ptr,
			&mlx_resources->bits_per_pixel, &mlx_resources->size_line,
			&mlx_resources->endian);
	if (!mlx_resources->img_addr)
		clean_up_and_exit(6, mlx_resources, coords);
	return ;
}

void	get_colour_gradient_rates(int colour_1, int colour_2,
	t_drawing_resources *drawing_resources)
{
	int		r_colour_difference;
	int		g_colour_difference;
	int		b_colour_difference;

	drawing_resources->r_gradient_rate = 0;
	drawing_resources->g_gradient_rate = 0;
	drawing_resources->b_gradient_rate = 0;
	if (colour_1 != colour_2)
	{
		r_colour_difference = (colour_2 >> 16) - (colour_1 >> 16);
		g_colour_difference = ((colour_2 >> 8) & 0xFF) - ((colour_1 >> 8)
				& 0xFF);
		b_colour_difference = (colour_2 & 0xFF) - (colour_1 & 0xFF);
		drawing_resources->r_gradient_rate
			= (float)r_colour_difference / (float)drawing_resources->steps;
		drawing_resources->g_gradient_rate
			= (float)g_colour_difference / (float)drawing_resources->steps;
		drawing_resources->b_gradient_rate
			= (float)b_colour_difference / (float)drawing_resources->steps;
	}
	return ;
}

void	draw_pixel(t_minilibx_resources mlx_resources, t_coordinates *coord)
{
	int		row;
	int		column;
	char	*dest;

	row = (int)coord->projected_y * mlx_resources.size_line;
	column = (int)coord->projected_x * (mlx_resources.bits_per_pixel / 8);
	dest = mlx_resources.img_addr + row + column;
	*(int *)dest = coord->colour;
	return ;
}

void	manage_colour_grading(int *colour,
	t_drawing_resources drawing_resources)
{
	static float	floating_r;
	static float	floating_g;
	static float	floating_b;

	if (!floating_r && !floating_g && !floating_b)
	{
		floating_r = *colour >> 16;
		floating_g = *colour >> 8;
		floating_b = *colour & 0xFF;
	}
	floating_r += drawing_resources.r_gradient_rate;
	floating_g += drawing_resources.g_gradient_rate;
	floating_b += drawing_resources.b_gradient_rate;
	*colour = ((int)floating_r << 16) | ((int)floating_g << 8)
		| (int)floating_b;
	if (drawing_resources.steps == 1)
	{
		floating_r = 0;
		floating_g = 0;
		floating_b = 0;
	}
	return ;
}

void	get_lower_coord(t_coordinates *coords, t_coordinates **lower_coord,
	t_rendering_resources render_resources)
{
	int	coord_nbr;

	*lower_coord = coords;
	coord_nbr = 1;
	while (coord_nbr <= render_resources.row_length)
	{
		*lower_coord = (*lower_coord)->next;
		coord_nbr++;
	}
	return ;
}
