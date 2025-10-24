/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structural_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-17 16:14:43 by elara-va          #+#    #+#             */
/*   Updated: 2025-10-17 16:14:43 by elara-va         ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	extension_check(char *filename, char *ext)
{
	char	**str_arr;
	int		return_value;

	return_value = 0;
	str_arr = ft_split(filename, '.');
	if (str_arr != NULL)
	{
		if (ft_listlen(str_arr) == 2 && ft_strncmp(str_arr[1], ext, 4) == 0)
			return_value = 1;
		free_str_arr(str_arr);
	}
	return (return_value);
}

void	argument_check(int ac, char *av[])
{
	size_t	i;

	i = 1;

	if (ac != 2 || !extension_check(av[1], "fdf")) 
	{
		ft_printf("Enter exactly one coordinates file with .fdf extension\n");
		exit(EXIT_FAILURE);
	}
	return ;
}