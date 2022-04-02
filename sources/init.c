/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:58:49 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:21:19 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"

void
	init_map_array(t_info *info)
{
	int	i;

	i = 0;
	info->map = (char **)ft_calloc(sizeof(char *) * (info->height_max + 1), 1);
	if (!info->map)
		system_error("Malloc Failed");
	while (i < info->height_max)
	{
		info->map[i] = \
		(char *)ft_calloc(sizeof(char) * (info->width_max + 1), 1);
		if (!info->map[i])
			system_error("Malloc Failed");
		i++;
	}
}

static int
	init_texture(t_info *info)
{
	int	i;

	info->texture = (int **)malloc(sizeof(int *) * 4);
	if (!info->texture)
		return (EXIT_FAILURE);
	i = 0;
	while (i < 4)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (TEX_W * TEX_H));
		if (!info->texture[i])
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int
	init_mlx(t_info *info)
{
	info->screen_w = SCREEN_W;
	info->screen_h = SCREEN_H;
	info->mlx_ptr = mlx_init();
	if (!info->mlx_ptr)
		return (EXIT_FAILURE);
	info->win_ptr = \
	mlx_new_window(info->mlx_ptr, info->screen_w, info->screen_h, "Cub3D");
	if (!info->win_ptr)
		return (EXIT_FAILURE);
	info->img = \
	mlx_new_image(info->mlx_ptr, info->screen_w, info->screen_h);
	if (!info->img)
		return (EXIT_FAILURE);
	info->img_addr = \
	mlx_get_data_addr(info->img, &info->bpp, &info->line_size, &info->endian);
	if (!info->img_addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_info
	*init(t_info *info)
{
	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	if (init_mlx(info))
		return (NULL);
	if (init_texture(info))
		return (NULL);
	info->list = create_linked_list();
	if (!info->list)
		return (NULL);
	return (info);
}
