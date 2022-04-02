/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:59:00 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:39:36 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void
	fill_blank(t_info *info, t_node *node, int i)
{
	int	j;

	if (ft_strlen(node->map) < (size_t)info->width_max)
	{
		j = ft_strlen(node->map);
		while (j < info->width_max)
			info->map[i][j++] = ' ';
		info->map[i][info->width_max] = '\0';
	}
}

void
	dup_map(t_info *info)
{
	t_node	*node;
	t_node	*temp;
	int		i;

	node = info->list->head;
	i = 0;
	while (node)
	{
		ft_strlcpy(info->map[i], node->map, ft_strlen(node->map) + 1);
		fill_blank(info, node, i);
		temp = node;
		node = node->next;
		free(temp->map);
		free(temp);
		info->list->size--;
		i++;
	}
	info->map[i] = NULL;
	free(info->list);
}

static int
	check_position(t_info *info, int i, int j)
{
	if (i - 1 < 0 || j - 1 < 0 || \
	i + 1 > info->height_max || j + 1 > info->width_max)
		return (EXIT_FAILURE);
	if (info->map[i - 1][j] != '0' && info->map[i - 1][j] != '1')
		return (EXIT_FAILURE);
	if (info->map[i][j - 1] != '0' && info->map[i][j - 1] != '1')
		return (EXIT_FAILURE);
	if (info->map[i + 1][j] != '0' && info->map[i + 1][j] != '1')
		return (EXIT_FAILURE);
	if (info->map[i][j + 1] != '0' && info->map[i][j + 1] != '1')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int
	check_blank(t_info *info, int i, int j)
{
	if (i - 1 > 0)
		if (info->map[i - 1][j] != ' ' && info->map[i - 1][j] != '1')
			return (EXIT_FAILURE);
	if (j - 1 > 0)
		if (info->map[i][j - 1] != ' ' && info->map[i][j - 1] != '1')
			return (EXIT_FAILURE);
	if (i + 1 < info->height_max)
		if (info->map[i + 1][j] != ' ' && info->map[i + 1][j] != '1')
			return (EXIT_FAILURE);
	if (j + 1 < info->width_max)
		if (info->map[i][j + 1] != ' ' && info->map[i][j + 1] != '1')
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int
	get_map_info(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->height_max)
	{
		j = 0;
		while (j < info->width_max)
		{
			if (ft_isalpha(info->map[i][j]))
			{
				if (check_position(info, i, j))
					return (error_return("Map: Invalid Start Position"));
				store_info(info, i, j);
			}
			if (info->map[i][j] == ' ')
				if (check_blank(info, i, j))
					return (error_return("Map: Invalid Blank Error"));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
