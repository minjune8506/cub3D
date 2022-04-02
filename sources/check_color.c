/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 23:40:24 by minjkim2          #+#    #+#             */
/*   Updated: 2022/04/02 01:16:13 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int
	is_valid_color(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int
	check_color_value(char **split, int i, int *color)
{
	if (!is_valid_color(split[i]))
	{
		free_double_char_ary(split);
		return (error_return("Color: Invalid RGB Error"));
	}
	*color = ft_atoi(split[i]);
	if (*color < 0 || *color > 255)
	{
		free_double_char_ary(split);
		return (error_return("Color: RGB Range Error"));
	}
	return (EXIT_SUCCESS);
}

static int
	check_comma(char *line)
{
	int	comma;
	int	i;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma == 2)
		return (EXIT_SUCCESS);
	return (error_return("Color: Two Many Commas Error"));
}

int
	check_color_info(char *line)
{
	char	**split;

	if (check_comma(line))
		return (EXIT_FAILURE);
	split = ft_split(line, ' ');
	if (!split)
		system_error("Color: Malloc Failed Error");
	if (ft_splitlen(split) < 2 || ft_splitlen(split) > 4)
	{
		free_double_char_ary(split);
		return (error_return("Color: Invalid Information Error"));
	}
	free_double_char_ary(split);
	return (EXIT_SUCCESS);
}
