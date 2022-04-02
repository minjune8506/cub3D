/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:59:02 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:31:18 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <fcntl.h>

static void
	load_texture(t_info *info, int dir, char *path)
{
	t_img	img;
	int		y;
	int		x;

	y = 0;
	img.img = \
	mlx_xpm_file_to_image(info->mlx_ptr, path, &img.img_width, &img.img_height);
	img.data = \
	(int *)mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			info->texture[dir][img.img_width * y + x] = \
			img.data[img.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx_ptr, img.img);
}

static char
	**parse_tex(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		system_error("Tex: Malloc Failed Error");
	if (ft_splitlen(split) != 2 || check_extension(split[1], ".xpm"))
	{
		free_double_char_ary(split);
		return (NULL);
	}
	return (split);
}

static int
	get_texture(char *line, t_info *info, int dir)
{
	char	**split;
	int		fd;

	split = parse_tex(line);
	if (!split)
		return (error_return("Tex: Information Is Invalid Error"));
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
		system_error("Tex: Invalid Path Error");
	load_texture(info, dir, split[1]);
	free_double_char_ary(split);
	info->dir_flag++;
	return (EXIT_SUCCESS);
}

int
	get_textures(t_info *info, char *line)
{
	if (info->dir_flag >= 4)
		return (error_return(".cub: Too Much Information Error"));
	if (!ft_strncmp(line, "NO", 2))
	{
		if (get_texture(line, info, NO))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (get_texture(line, info, EA))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (get_texture(line, info, SO))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (get_texture(line, info, WE))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
