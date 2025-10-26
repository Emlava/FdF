/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-28 14:18:44 by elara-va          #+#    #+#             */
/*   Updated: 2025-09-28 14:18:44 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	image_size_check(t_rendering_resources *render_resources)
{
	int	width_needed;
	int	heigth_needed;

	width_needed = render_resources->greatest_projected_x * 2;
	heigth_needed = render_resources->greatest_projected_y * 2;
	if (width_needed > render_resources->screen_width
		|| heigth_needed > render_resources->screen_hight)
		return (0);
	else
		return (1);
}

int	adjust_coords_into_frame(t_coordinates *coords,
	t_rendering_resources *render_resources)
{
	int	to_frame_x;
	int	to_frame_y;

	(void) coords;

	to_frame_x = -render_resources->lowest_projected_x;
	to_frame_y = -render_resources->lowest_projected_y;
	render_resources->greatest_projected_x += to_frame_x;
	render_resources->greatest_projected_y += to_frame_y;
	if (!image_size_check(render_resources))
		return (0);
	while (coords != NULL)
	{
		coords->projected_x += to_frame_x + X_OFFSET;
		coords->projected_y += to_frame_y + Y_OFFSET;
		coords = coords->next;
	}
	return (1);
}

int	ishex(char *str)
{
	size_t	i;

	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		i = 2;
		while (str[i] && i < 8 && ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'A' && str[i] <= 'F')
			|| (str[i] >= 'a' && str[i] <= 'f')))
			i++;
		if (!str[i])
			return (1);
	}
	return (0);
}
