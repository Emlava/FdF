/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-18 13:18:44 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-18 13:18:44 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_row(t_map_resources *map, t_minilibx_resources mlx_resources,
	t_coordinates *coords, t_rendering_resources *render_resources)
{
	map->gnl_str = get_next_line(map->fd);
	if (!map->gnl_str)
		return (0);
	map->row = ft_split(map->gnl_str, ' ');
	if (!map->row)
		clean_up_and_exit(3, map, &mlx_resources, coords);
	if (!check_for_valid_row_length(render_resources, *map))
		clean_up_and_exit(4, map, &mlx_resources, coords);
	return (1);
}

static void	parse_str_from_row(t_map_resources map,
	t_minilibx_resources mlx_resources, t_coordinates *coords)
{
	while (1)
	{
		if (ft_isdigit(map.row[map.x][map.i])
			|| (map.i == 0 && map.row[map.x][map.i] == '-'
			&& ft_isdigit(map.row[map.x][map.i + 1])))
		{
			if (map.row[map.x][map.i] == '-')
				map.i += 2;
			else
				map.i++;
			if (!map.row[map.x][map.i] || map.row[map.x][map.i] == '\n')
			{
				coords->colour = 0xFFFFFF;
				return ;
			}
		}
		else if (!manage_colour(map, coords))
			clean_up_and_exit(4, &map, &mlx_resources, coords);
		else
			return ;
	}
}

static void	apply_projecting_formulas(t_coordinates *coords,
	t_map_resources map)
{
	int			projection_formula_for_x;
	int			projection_formula_for_y;

	coords->z = ft_atoi(map.row[map.x]);
	map.x *= SCALE;
	map.y *= SCALE;
	coords->z *= SCALE;
	projection_formula_for_x = (map.x - map.y) * cos(PI / 6);
	projection_formula_for_y = (map.x + map.y) * sin(PI / 6) - coords->z;
	coords->projected_x = projection_formula_for_x;
	coords->projected_y = projection_formula_for_y;
	return ;
}

static void	project_coordinates(t_map_resources *map,
	t_minilibx_resources mlx_resources, t_coordinates *coords,
	t_rendering_resources *render_resources)
{
	while (1)
	{
		map->x = 0;
		if (!parse_row(map, mlx_resources, coords, render_resources))
			return ;
		while (map->x < render_resources->row_length)
		{
			if (map->y > 0 || map->x > 0)
			{
				if (!create_next_node(&coords))
					clean_up_and_exit(4, map, &mlx_resources, coords);
			}
			parse_str_from_row(*map, mlx_resources, coords);
			apply_projecting_formulas(coords, *map);
			look_for_greatest_and_lowest_points(coords, render_resources);
			map->x++;
		}
		map->y++;
		free(map->gnl_str);
		free_str_arr(map->row);
	}
}

void	manage_file_coordinates(char *file, t_coordinates **coords,
	t_minilibx_resources *mlx_resources,
	t_rendering_resources *render_resources)
{
	t_map_resources	map;

	map.fd = open(file, O_RDONLY);
	if (map.fd == -1)
	{
		ft_dprintf(2, "Failed to open %s\n", file);
		exit(EXIT_FAILURE);
	}
	assign_various_resources(&map, coords, mlx_resources, render_resources);
	project_coordinates(&map, *mlx_resources, *coords, render_resources);
	render_resources->nbr_of_rows = map.y;
	if (!adjust_coords_into_frame(*coords, render_resources))
	{
		ft_dprintf(2, "Image too large, try defining a lower SCALE\n");
		clean_up_and_exit(5, mlx_resources, *coords);
	}
	close(map.fd);
	return ;
}
