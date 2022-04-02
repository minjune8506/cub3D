/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:39 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:47:54 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void
	perform_dda(t_info *info, t_calc *calc)
{
	calc->hit = 0;
	while (calc->hit == 0)
	{
		if (calc->sidedistx < calc->sidedisty)
		{
			calc->sidedistx += calc->deltadistx;
			calc->map_x += calc->stepx;
			calc->side = 0;
		}
		else
		{
			calc->sidedisty += calc->deltadisty;
			calc->map_y += calc->stepy;
			calc->side = 1;
		}
		if (info->map[calc->map_x][calc->map_y] == '1')
			calc->hit = 1;
	}
	if (calc->side == 0)
		calc->walldist = (calc->map_x - info->ray.pos_x + \
		(1 - calc->stepx) / 2) / calc->raydirx;
	else
		calc->walldist = (calc->map_y - info->ray.pos_y + \
		(1 - calc->stepy) / 2) / calc->raydiry;
}

static void
	get_tex(t_calc *calc)
{
	if (calc->raydirx > 0 && calc->side == 0)
		calc->texnum = NO;
	else if (calc->raydirx < 0 && calc->side == 0)
		calc->texnum = SO;
	else if (calc->raydiry > 0 && calc->side == 1)
		calc->texnum = WE;
	else
		calc->texnum = EA;
}

static void
	init_wall_tex(t_info *info, t_calc *calc)
{
	double	wallx;

	calc->line_height = (int)(info->screen_h / calc->walldist);
	calc->draw_start = -calc->line_height / 2 + info->screen_h / 2;
	if (calc->draw_start < 0)
		calc->draw_start = 0;
	calc->draw_end = calc->line_height / 2 + info->screen_h / 2;
	if (calc->draw_end >= info->screen_h)
		calc->draw_end = info->screen_h - 1;
	get_tex(calc);
	if (calc->side == 0)
		wallx = info->ray.pos_y + calc->walldist * calc->raydiry;
	else
		wallx = info->ray.pos_x + calc->walldist * calc->raydirx;
	wallx -= floor(wallx);
	calc->tex_x = (int)(wallx * (double)TEX_W);
	if (calc->side == 0 && calc->raydirx > 0)
		calc->tex_x = TEX_W - calc->tex_x - 1;
	if (calc->side == 1 && calc->raydiry < 0)
		calc->tex_x = TEX_W - calc->tex_x - 1;
}

static void
	draw_wall_tex(t_info *info, t_calc *calc, int x)
{
	int		tex_y;
	int		color;
	double	step;
	int		y;

	step = 1.0 * TEX_H / calc->line_height;
	calc->texpos = (calc->draw_start - info->screen_h / 2 + \
	calc->line_height / 2) * step;
	y = -1;
	while (++y < info->screen_h)
	{
		if (y >= calc->draw_start && y < calc->draw_end)
		{
			tex_y = (int)calc->texpos & (TEX_H - 1);
			calc->texpos += step;
			color = info->texture[calc->texnum][TEX_H * tex_y + calc->tex_x];
			if (calc->side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(info, x, y, color);
		}
		else if (y < calc->draw_start)
			my_mlx_pixel_put(info, x, y, info->ceil_color);
		else if (y >= calc->draw_end)
			my_mlx_pixel_put(info, x, y, info->floor_color);
	}
}

void
	draw(t_info *info)
{
	t_calc	calc;
	int		x;

	x = 0;
	while (x < info->screen_w)
	{
		start_ray(info, &calc, x);
		init_dda(info, &calc);
		perform_dda(info, &calc);
		init_wall_tex(info, &calc);
		draw_wall_tex(info, &calc, x);
		x++;
	}
}
