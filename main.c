/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-21 10:23:01 by elara-va          #+#    #+#             */
/*   Updated: 2025-09-21 10:23:01 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	display_image(t_minilibx_resources mlx_resources,
	t_rendering_resources render_resources, char *file_name)
{
	mlx_resources.win_ptr = mlx_new_window(mlx_resources.mlx_ptr, render_resources.largest_projected_x + WINDOW_MARGIN,
		render_resources.largest_projected_y + WINDOW_MARGIN, file_name);
	if (!mlx_resources.win_ptr)
		clean_up_and_exit(7, mlx_resources); // Instance 7
	mlx_hook(mlx_resources.win_ptr, KeyPress, KeyPressMask, manage_esc, &mlx_resources);
	mlx_hook(mlx_resources.win_ptr, DestroyNotify, StructureNotifyMask, manage_cross, &mlx_resources);
	mlx_put_image_to_window(mlx_resources.mlx_ptr, mlx_resources.win_ptr, mlx_resources.img_ptr,
		0, 0);
	mlx_loop(mlx_resources.mlx_ptr);
}

int	main(int ac, char *av[])
{
	t_coordinates			*coords;
	t_minilibx_resources	mlx_resources;
	t_rendering_resources	render_resources;


	argument_check(ac, av);
	manage_file_coordinates(av[1], &coords, &mlx_resources, &render_resources);
	create_image(&mlx_resources, render_resources, coords);
	display_image(mlx_resources, render_resources, av[1]);
	return (0);
}

/*
Things to free/close:
-coords;
-gnl_str
-row and each row[i]
-fd (close)
-mlx_ptr
-img_ptr
-win_ptr

Note: img_addr is freed when the image is destroyed
*/
