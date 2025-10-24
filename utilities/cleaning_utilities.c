/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-11 10:21:59 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-11 10:21:59 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_linked_list(t_coordinates *list)
{
	t_coordinates	*tmp;

	if (list == NULL)
		return ;
	while (list->next != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	free(list);
	return ;
}

void	free_str_arr(char **str_arr)
{
	size_t	i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while(str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return ;
}

// Instance 1 or 2: close fd
// Instance 3: close fd, free gnl_str
// Instance 4: close fd, free gnl_str and row 
static void	map_clean_up(int instance, t_map_resources map)
{
	close(map.fd);
	if (instance >= 3)
	{
		free(map.gnl_str);
		if (instance == 4)
			free_str_arr(map.row);
	}
	return ;
}

// Instance 1: destroy display and free mlx_ptr
// Instance 2: destroy image and display, and free mlx_ptr
// Instance 3: destroy image, window and display, and free mlx_ptr
void	mlx_clean_up(int instance, t_minilibx_resources mlx_resources)
{
	if (instance > 1)
	{
		mlx_destroy_image(mlx_resources.mlx_ptr, mlx_resources.img_ptr);
		if (instance == 3)
			mlx_destroy_window(mlx_resources.mlx_ptr, mlx_resources.win_ptr);
	}
	mlx_destroy_display(mlx_resources.mlx_ptr);
	free(mlx_resources.mlx_ptr);
	return ;
}

// Instance 1: close fd
// Instance 2: close fd, destroy display and free mlx_ptr
// Instance 3: close fd, free gnl_str, destroy display and free mlx_ptr and coords
// Instance 4: close fd, free gnl_str and row, destroy display and free mlx_ptr and coords
// Instance 5: destroy display and free mlx_ptr and coords
// Instance 6: destroy image and display, and free mlx_ptr and coords
// Instance 7: destroy image and display, and free mlx_ptr
// Always exits with EXIT_FAILURE
void	clean_up_and_exit(int instance, ...)
{
	va_list					arg_list;
	t_map_resources			map;
	t_minilibx_resources	mlx_resources;

	va_start(arg_list, instance);
	if (instance <= 4)
	{
		// For Insts 1-4: arg 2
		map = va_arg(arg_list, t_map_resources);
		map_clean_up(instance, map);
	}
	if (instance >= 2)
	{
		// For Insts 2-4: arg 3
		// For Insts 5-7: arg 2
		mlx_resources = va_arg(arg_list, t_minilibx_resources);
		if (instance != 6)
			mlx_clean_up(1, mlx_resources);
		else
			mlx_clean_up(2, mlx_resources);
	}
	if (instance >= 3 && instance <= 6)
		// For Insts 3-4: arg 4
		// For Insts 5-6: arg 3
		free_linked_list(va_arg(arg_list, t_coordinates*));
	va_end(arg_list);
	exit(EXIT_FAILURE);
}
