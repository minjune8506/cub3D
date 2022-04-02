/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 23:28:11 by minjkim2          #+#    #+#             */
/*   Updated: 2022/04/02 00:43:36 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	store_dir_ew(t_info *info, int i, int j)
{
	if (info->map[i][j] == 'E')
	{
		info->ray.dir_x = 0;
		info->ray.dir_y = 1;
		info->ray.plane_x = 0.66;
		info->ray.plane_y = 0;
	}
	else if (info->map[i][j] == 'W')
	{
		info->ray.dir_x = 0;
		info->ray.dir_y = -1;
		info->ray.plane_x = -0.66;
		info->ray.plane_y = 0;
	}
}

static void
	store_dir_sn(t_info *info, int i, int j)
{
	if (info->map[i][j] == 'S')
	{
		info->ray.dir_x = 1;
		info->ray.dir_y = 0;
		info->ray.plane_x = 0;
		info->ray.plane_y = -0.66;
	}
	else if (info->map[i][j] == 'N')
	{
		info->ray.dir_x = -1;
		info->ray.dir_y = 0;
		info->ray.plane_x = 0;
		info->ray.plane_y = 0.66;
	}
}

void
	store_info(t_info *info, int i, int j)
{
	info->ray.pos_x = i + 0.5;
	info->ray.pos_y = j + 0.5;
	if (info->map[i][j] == 'E' || info->map[i][j] == 'W')
		store_dir_ew(info, i, j);
	else if (info->map[i][j] == 'S' || info->map[i][j] == 'N')
		store_dir_sn(info, i, j);
}
