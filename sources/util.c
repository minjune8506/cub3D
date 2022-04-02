/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:59:06 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:50:59 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

unsigned int
	get_color(int *rgb)
{
	return (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void
	my_mlx_pixel_put(t_info *info, int x, int y, unsigned int color)
{
	char	*dst;

	dst = info->img_addr + (y * info->line_size + x * (info->bpp / 8));
	*(unsigned int *)dst = color;
}

int
	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void
	free_double_char_ary(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

int
	check_extension(char *filename, char *extension)
{
	if (!filename)
		return (EXIT_FAILURE);
	if (ft_strncmp(filename + ft_strlen(filename) - 4, extension, 4))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
