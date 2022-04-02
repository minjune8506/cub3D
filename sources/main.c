/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Minjun <Minjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:54 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/03 00:24:38 by Minjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void
	free_double_ptr(void **ptr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(ptr[i++]);
	free(ptr);
}

void
	check_input(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		error_exit("Input Argument Error");
	else
	{
		if (check_extension(av[1], ".cub"))
			error_exit("File Extension Error");
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			system_error(".cub Path Error");
		if (close(fd) < 0)
			system_error("Close Failed Error");
	}
}

void
	deinitialize(t_info *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	free_double_ptr((void **)info->texture, 4);
	free(info);
}

static int
	main_event(t_info *info)
{
	draw(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img, 0, 0);
	player_move(info);
	return (0);
}

int
	main(int ac, char **av)
{
	t_info	*info;

	info = NULL;
	check_input(ac, av);
	info = init(info);
	if (!info)
		system_error("cub3D initialize Fail");
	if (parse(av, info))
		exit(1);
	init_map_array(info);
	dup_map(info);
	if (get_map_info(info))
		exit(1);
	mlx_loop_hook(info->mlx_ptr, main_event, info);
	mlx_hook(info->win_ptr, KEY_PRESS, 0, key_pressed, info);
	mlx_hook(info->win_ptr, KEY_RELEASE, 0, key_released, info);
	mlx_hook(info->win_ptr, ON_DESTROY, 0, close_button, info);
	mlx_loop(info->mlx_ptr);
}
