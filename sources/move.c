/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:58 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:45:57 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

static int
	move_up(t_info *info)
{
	double	movespeed;

	movespeed = 0.08;
	if (info->map[(int)(info->ray.pos_x + info->ray.dir_x * movespeed)] \
	[(int)info->ray.pos_y] != '1')
		info->ray.pos_x += info->ray.dir_x * movespeed;
	if (info->map[(int)info->ray.pos_x] \
	[(int)(info->ray.pos_y + info->ray.dir_y * movespeed)] != '1')
		info->ray.pos_y += info->ray.dir_y * movespeed;
	return (0);
}

static int
	move_down(t_info *info)
{
	double	movespeed;

	movespeed = 0.08;
	if (info->map[(int)(info->ray.pos_x - info->ray.dir_x * movespeed)] \
	[(int)(info->ray.pos_y)] != '1')
		info->ray.pos_x -= info->ray.dir_x * movespeed;
	if (info->map[(int)(info->ray.pos_x)] \
	[(int)(info->ray.pos_y - info->ray.dir_y * movespeed)] != '1')
		info->ray.pos_y -= info->ray.dir_y * movespeed;
	return (0);
}

static void
	rotate_vector(t_info *info, double rotSpeed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = info->ray.dir_x;
	info->ray.dir_x = \
	info->ray.dir_x * cos(rotSpeed) - info->ray.dir_y * sin(rotSpeed);
	info->ray.dir_y = \
	old_dirx * sin(rotSpeed) + info->ray.dir_y * cos(rotSpeed);
	old_planex = info->ray.plane_x;
	info->ray.plane_x = \
	info->ray.plane_x * cos(rotSpeed) - info->ray.plane_y * sin(rotSpeed);
	info->ray.plane_y = \
	old_planex * sin(rotSpeed) + info->ray.plane_y * cos(rotSpeed);
}

void
	player_move(t_info *info)
{
	if (info->keynum.key_a)
		rotate_vector(info, 0.05);
	if (info->keynum.key_d)
		rotate_vector(info, -0.05);
	if (info->keynum.key_s)
		move_down(info);
	if (info->keynum.key_w)
		move_up(info);
}
