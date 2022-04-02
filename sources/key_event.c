/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:51 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 01:23:31 by Minjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int
	close_window(t_info *info)
{
	free_double_ptr((void **)info->map, info->height_max + 1);
	deinitialize(info);
	exit(1);
	return (0);
}

int
	key_pressed(int keycode, t_info *info)
{
	if (keycode == ESC)
		close_window(info);
	if (keycode == KEY_W)
		info->keynum.key_w = 1;
	if (keycode == KEY_S)
		info->keynum.key_s = 1;
	if (keycode == KEY_D || keycode == RIGHT_ARROW)
		info->keynum.key_d = 1;
	if (keycode == KEY_A || keycode == LEFT_ARROW)
		info->keynum.key_a = 1;
	return (0);
}

int
	key_released(int keycode, t_info *info)
{
	if (keycode == ESC)
		close_window(info);
	if (keycode == KEY_W)
		info->keynum.key_w = 0;
	if (keycode == KEY_S)
		info->keynum.key_s = 0;
	if (keycode == KEY_D || keycode == RIGHT_ARROW)
		info->keynum.key_d = 0;
	if (keycode == KEY_A || keycode == LEFT_ARROW)
		info->keynum.key_a = 0;
	return (0);
}

int
	close_button(t_info *info)
{
	free_double_char_ary(info->map);
	deinitialize(info);
	exit(1);
}
