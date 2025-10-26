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

static void	draw_single_pixel(t_coordinates *coord,
	t_minilibx_resources mlx_resources)
{
	int		row;
	int		column;
	char	*dest;

	row = coord->projected_y * mlx_resources.size_line;
	column = coord->projected_x * (mlx_resources.bits_per_pixel / 8);
	dest = mlx_resources.img_addr + row + column;
	*(int*)dest = coord->colour;
	return ;
}

static void	draw_rows(t_coordinates *coords, t_rendering_resources render_resources,
	t_minilibx_resources mlx_resources)
{
	int	lines_in_row;
	int	lines_to_draw;

	lines_in_row = render_resources.row_length - 1;
	lines_to_draw = lines_in_row;
	while (coords->next != NULL)
	{
		if (lines_to_draw)
		{
			draw_line(*coords, *coords->next, mlx_resources);
			lines_to_draw--;
		}
		else
			lines_to_draw = lines_in_row;
		coords = coords->next;
	}
	return ;
}

static void	draw_columns(t_coordinates *coords, t_rendering_resources render_resources,
	t_minilibx_resources mlx_resources)
{
	t_coordinates	*upper_coord;
	t_coordinates	*lower_coord;

	upper_coord = coords;
	get_lower_coord(coords, &lower_coord, render_resources);
	while (lower_coord != NULL)
	{
		draw_line(*upper_coord, *lower_coord, mlx_resources);
		upper_coord = upper_coord->next;
		lower_coord = lower_coord->next;
	}
	return ;
}

static void	draw_image(t_coordinates *coords,
	t_rendering_resources render_resources, t_minilibx_resources mlx_resources)
{
	if (render_resources.nbr_of_rows == 1 && render_resources.row_length == 1)
		draw_single_pixel(coords, mlx_resources);
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
	t_rendering_resources render_resources, t_coordinates *coords)
{
	initialize_mlx_resources(mlx_resources, render_resources, coords);
	draw_image(coords, render_resources, *mlx_resources);
	free_linked_list(coords);
	return ;
}
