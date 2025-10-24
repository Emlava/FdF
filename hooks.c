/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 18:10:26 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-14 18:10:26 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	manage_esc(int keycode, void *mlx_resources)
{
	if (keycode == 0xff1b)
		mlx_clean_up(3, *(t_minilibx_resources*)mlx_resources);
	exit(EXIT_SUCCESS);
}

int	manage_cross(void *mlx_resources)
{
	mlx_clean_up(3, *(t_minilibx_resources*)mlx_resources);
	exit(EXIT_SUCCESS);
}
