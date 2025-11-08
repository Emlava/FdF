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

static int	image_size_check(t_rendering_resources *render_resources)
{
	render_resources->image_width = (MARGIN * 2)
		+ render_resources->greatest_projected_x + 1;
	render_resources->image_height = (MARGIN * 2)
		+ render_resources->greatest_projected_y + 1;
	if (render_resources->image_width > render_resources->screen_width
		|| render_resources->image_height > render_resources->screen_hight)
		return (0);
	else
		return (1);
}

int	adjust_coords_into_frame(t_coordinates *coords,
	t_rendering_resources *render_resources)
{
	int	to_frame_x;
	int	to_frame_y;

	to_frame_x = -render_resources->lowest_projected_x;
	to_frame_y = -render_resources->lowest_projected_y;
	render_resources->greatest_projected_x += to_frame_x;
	render_resources->greatest_projected_y += to_frame_y;
	if (!image_size_check(render_resources))
		return (0);
	while (coords != NULL)
	{
		coords->projected_x += to_frame_x + (MARGIN - 1);
		coords->projected_y += to_frame_y + (MARGIN - 1);
		coords = coords->next;
	}
	return (1);
}

int	ishex(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
	{
		i += 2;
		while (str[i] && ((str[i] >= '0' && str[i] <= '9')
				|| (str[i] >= 'A' && str[i] <= 'F')
				|| (str[i] >= 'a' && str[i] <= 'f')))
			i++;
		if (!str[i] || str[i] == '\n')
			return (1);
	}
	return (0);
}
