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
	t_minilibx_resources *mlx_resources,
	t_rendering_resources *render_resources)
{
	mlx_resources->mlx_ptr = mlx_init();
	if (!mlx_resources->mlx_ptr)
		clean_up_and_exit(1, map);
	mlx_get_screen_size(mlx_resources->mlx_ptr, &render_resources->screen_width,
		&render_resources->screen_hight);
	*coords = malloc(sizeof(t_coordinates));
	if (!(*coords))
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
		if (get_row_length(map.row) == render_resources->row_length)
			return (1);
	}
	else
	{
		render_resources->row_length = get_row_length(map.row);
		if (render_resources->row_length != 0)
			return (1);
	}
	ft_dprintf(2,
		"Invalid .fdf file: Invalid line length found in line %d\n",
		map.y + 1);
	return (0);
}

int	create_next_node(t_coordinates **coords)
{
	(*coords)->next = malloc(sizeof(t_coordinates));
	if (!(*coords)->next)
		return (0);
	(*coords)->next->prev = *coords;
	*coords = (*coords)->next;
	(*coords)->next = NULL;
	return (1);
}

int	manage_colour(t_map_resources map, t_coordinates *coords)
{
	if (map.row[map.x][map.i] == ',')
	{
		if (ishex(map.row[map.x] + (map.i + 1)))
		{
			coords->colour = ft_hexatoi(map.row[map.x] + (map.i + 1));
			if (coords->colour >= 0 && coords->colour <= 0xFFFFFF)
				return (1);
		}
		ft_dprintf(2, "Invalid .fdf file: non-existent colour found");
		ft_dprintf(2, " in line %d, column %d\n", map.y + 1, map.x + 1);
	}
	else
	{
		ft_dprintf(2, "Invalid .fdf file: Invalid coordinate found");
		ft_dprintf(2, " in line %d, column %d\n", map.y + 1, map.x + 1);
	}
	return (0);
}
