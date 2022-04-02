/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:59 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:55:15 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int
	get_value(char *str, int *count, int *rgb)
{
	char	**split;
	int		color;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		system_error("Color: Malloc Failed Error");
	i = 0;
	while (split[i])
	{
		color = -1;
		if (check_color_value(split, i, &color))
			return (EXIT_FAILURE);
		if (*count > 2)
		{
			free_double_char_ary(split);
			return (error_return("Color: Too Many Colors Error"));
		}
		rgb[*count] = color;
		*count += 1;
		i++;
	}
	free_double_char_ary(split);
	return (EXIT_SUCCESS);
}

static int
	parse_color(t_info *info, char *line, int flag)
{
	char	**split;
	int		rgb[3];
	int		count;
	int		i;

	if (check_color_info(line))
		return (EXIT_FAILURE);
	split = ft_split(line, ' ');
	i = 1;
	count = 0;
	while (split[i])
	{
		if (get_value(split[i++], &count, rgb))
		{
			free_double_char_ary(split);
			return (EXIT_FAILURE);
		}
	}
	if (flag == 0)
		info->floor_color = get_color(rgb);
	else
		info->ceil_color = get_color(rgb);
	info->color_flag++;
	free_double_char_ary(split);
	return (EXIT_SUCCESS);
}

int
	get_colors(t_info *info, char *line)
{
	if (info->color_flag >= 2)
		return (error_return(".cub: Too Much Information Error"));
	if (!ft_strncmp(line, "F", 1))
		if (parse_color(info, line, 0))
			return (EXIT_FAILURE);
	if (!ft_strncmp(line, "C", 1))
		if (parse_color(info, line, 1))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
