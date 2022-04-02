/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:59:03 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:37:40 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line_bonus.h"
#include "libft.h"
#include <fcntl.h>

static int
	get_map(t_info *info, char *line)
{
	t_node	*node;

	if (check_map(info, line, ft_strlen(line)))
		return (EXIT_FAILURE);
	node = create_new_node(line);
	if (!node)
		system_error("Map: Malloc Failed Error");
	add_node(info->list, node);
	if ((size_t)info->width_max < ft_strlen(line))
		info->width_max = ft_strlen(line);
	info->height_max++;
	return (EXIT_SUCCESS);
}

static int
	parse_line(t_info *info, char *line)
{
	if (info->dir_flag > 4 || info->color_flag > 2)
		return (error_return(".cub: Too Much Information Error"));
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) \
	|| !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		return (get_textures(info, line));
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (get_colors(info, line));
	if (ft_strlen(line) <= 0)
		return (EXIT_SUCCESS);
	if (info->color_flag == 2 && info->dir_flag == 4)
		return (get_map(info, line));
	return (error_return(".cub: Invalid Identifier Error"));
}

static int
	check_last_line(t_info *info)
{
	t_node	*node;
	int		i;
	int		size;

	node = info->list->tail;
	if (!node)
		return (error_return("Map: No Map Information"));
	i = 0;
	size = ft_strlen(node->map);
	while (i < size)
	{
		if (node->map[i] != '1' && node->map[i] != ' ')
			return (error_return("Map: Invalid Last Line Error"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int
	parse(char **av, t_info *info)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (!line)
			return (error_return("GNL Error"));
		if (parse_line(info, line))
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
	}
	if (check_last_line(info))
	{
		free(line);
		return (EXIT_FAILURE);
	}
	free(line);
	if (info->dir_flag != 4 || info->color_flag != 2 || info->pos_flag != 1)
		return (error_return(".cub: Too Few Information"));
	return (EXIT_SUCCESS);
}
