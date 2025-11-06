/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file_coordinates_utilities.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-18 15:41:51 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-18 15:41:51 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	assign_various_resources(t_map_resources *map, t_coordinates **coords,
	t_minilibx_resources *mlx_resources, t_rendering_resources *render_resources)
{
	mlx_resources->mlx_ptr = mlx_init();
	if (!mlx_resources->mlx_ptr) // Instance 1, close fd 
		clean_up_and_exit(1, map);
	mlx_get_screen_size(mlx_resources->mlx_ptr, &render_resources->screen_width,
		&render_resources->screen_hight);
	*coords = malloc(sizeof(t_coordinates));
	if (!(*coords)) // Instance 2, close fd and free mlx_ptr
		clean_up_and_exit(2, map, mlx_resources);
	(*coords)->next = NULL;
	(*coords)->prev = NULL;
	render_resources->row_length = -1;
	map->y = 0;
	map->i = 0;
	render_resources->greatest_projected_x = 0;
	render_resources->greatest_projected_y = 0;
	render_resources->lowest_projected_x = 0;
	render_resources->lowest_projected_y = 0;
	return ;
}

static int	get_row_length(char **row)
{
	int	i;

	i = 0;
	while (row[i] && row[i][0] != '\n')
		i++;
	return (i);
}

int	check_for_valid_row_length(t_rendering_resources *render_resources,
		t_map_resources map)
{
	if (render_resources->row_length != -1)
	{
		if (get_row_length(map.row) != render_resources->row_length)
		{
			ft_dprintf(2,
				"Invalid .fdf file: Wrong line length found in line %d\n",
				map.y + 1);
			return (0);
		}
	}
	else
		render_resources->row_length = get_row_length(map.row);
	return (1);
}

int	create_next_node(t_coordinates **coords)
{
	(*coords)->next = malloc(sizeof(t_coordinates)); // Initialize the members that you're going to use from coords
	if (!(*coords)->next)
		return (0);
	(*coords)->next->prev = *coords;
	*coords = (*coords)->next;
	(*coords)->next = NULL;
	return (1);
}

void	look_for_greatest_and_lowest_points(t_coordinates *coords,
	t_rendering_resources *render_resources)
{
	if (coords->projected_x < render_resources->lowest_projected_x)
		render_resources->lowest_projected_x = coords->projected_x;
	else if (coords->projected_x > render_resources->greatest_projected_x)
			render_resources->greatest_projected_x = coords->projected_x;
	if (coords->projected_y < render_resources->lowest_projected_y)
		render_resources->lowest_projected_y = coords->projected_y;
	else if (coords->projected_y > render_resources->greatest_projected_y)
		render_resources->greatest_projected_y = coords->projected_y;
	return ;
}
