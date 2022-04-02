/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 23:31:50 by minjkim2          #+#    #+#             */
/*   Updated: 2022/04/02 00:26:35 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static int
	check_map_contents(t_info *info, char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (info->pos_flag)
			return (error_return("Map: Spawn Position Invalid Error"));
		info->pos_flag = 1;
		return (EXIT_SUCCESS);
	}
	else if (c == ' ' || c == '0' || c == '1')
		return (EXIT_SUCCESS);
	return (error_return("Map: Invalid Character Error"));
}

static int
	check_first_line(char *line, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (line[i] != '1' && line[i] != ' ')
			return (error_return("Map: Invalid First Line Error"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int
	check_map(t_info *info, char *line, int size)
{
	int	i;

	i = 0;
	if (info->list->head == NULL)
	{
		if (check_first_line(line, size))
			return (EXIT_FAILURE);
	}
	else
	{
		while (i < size)
		{
			if (check_map_contents(info, line[i]))
				return (EXIT_FAILURE);
			i++;
		}
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1' && line[size - 1] != '1')
			return (error_return("Map: Invalid Middle Line Error"));
	}
	return (EXIT_SUCCESS);
}
