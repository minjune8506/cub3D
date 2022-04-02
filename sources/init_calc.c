/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 23:15:25 by minjkim2          #+#    #+#             */
/*   Updated: 2022/04/01 23:15:28 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void
	start_ray(t_info *info, t_calc *calc, int x)
{
	double	camerax;

	camerax = 2 * x / (double)info->screen_w - 1;
	calc->raydirx = info->ray.dir_x + info->ray.plane_x * camerax;
	calc->raydiry = info->ray.dir_y + info->ray.plane_y * camerax;
	calc->map_x = (int)info->ray.pos_x;
	calc->map_y = (int)info->ray.pos_y;
	calc->deltadistx = sqrt(1 + (calc->raydiry * calc->raydiry) \
	/ (calc->raydirx * calc->raydirx));
	calc->deltadisty = sqrt(1 + (calc->raydirx * calc->raydirx) \
	/ (calc->raydiry * calc->raydiry));
}

void
	init_dda(t_info *info, t_calc *calc)
{
	if (calc->raydirx < 0)
	{
		calc->stepx = -1;
		calc->sidedistx = (info->ray.pos_x - calc->map_x) * calc->deltadistx;
	}
	else
	{
		calc->stepx = 1;
		calc->sidedistx = (calc->map_x + 1.0 - info->ray.pos_x) \
		* calc->deltadistx;
	}
	if (calc->raydiry < 0)
	{
		calc->stepy = -1;
		calc->sidedisty = (info->ray.pos_y - calc->map_y) * calc->deltadisty;
	}
	else
	{
		calc->stepy = 1;
		calc->sidedisty = (calc->map_y + 1.0 - info->ray.pos_y) \
		* calc->deltadisty;
	}
}
