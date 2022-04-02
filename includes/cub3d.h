/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjkim2 <42.4.minjkim2@student.42seoul    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:59:16 by Minjun            #+#    #+#             */
/*   Updated: 2022/04/02 00:51:18 by minjkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>

# define TEX_W 64
# define TEX_H 64
# define SCREEN_W 960
# define SCREEN_H 640

enum e_key {
	ESC = 53,
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	LEFT_ARROW = 123,
	RIGHT_ARROW = 124,
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	ON_DESTROY = 17,
};

enum e_dir {
	NO = 0,
	EA = 1,
	SO = 2,
	WE = 3
};

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}t_ray;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}t_img;

typedef struct s_key
{
	char	key_w;
	char	key_s;
	char	key_a;
	char	key_d;
}t_key;

typedef struct s_calc
{
	double	raydirx;
	double	raydiry;
	int		map_x;
	int		map_y;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	walldist;
	int		stepx;
	int		stepy;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texnum;
	int		tex_x;
	double	texpos;
	int		hit;
}t_calc;

typedef struct s_node
{
	char			*map;
	struct s_node	*next;
}t_node;

typedef struct s_maplist
{
	t_node	*head;
	t_node	*tail;
	int		size;
}t_maplist;

typedef struct s_info
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*img_addr;
	int				bpp;
	int				line_size;
	int				endian;
	int				screen_w;
	int				screen_h;
	int				**texture;
	int				dir_flag;
	int				color_flag;
	int				pos_flag;
	unsigned int	floor_color;
	unsigned int	ceil_color;
	int				width_max;
	int				height_max;
	t_ray			ray;
	char			**map;
	t_key			keynum;
	t_maplist		*list;
}	t_info;

/**
 * init.c
 */
t_info			*init(t_info *info);
void			init_map_array(t_info *info);
/**
 * parse.c
 */
int				parse(char **av, t_info *info);
/**
 * check_map.c
 */
int				check_map(t_info *info, char *line, int size);
/**
 * list.c
 */
t_maplist		*create_linked_list(void);
t_node			*create_new_node(char *line);
void			add_node(t_maplist *list, t_node *node);
/**
 * parse_texture.c
 */
int				get_textures(t_info *info, char *line);
/**
 * parse_color.c
 */
int				get_colors(t_info *info, char *line);
/**
 * check_color.c
 */
int				check_color_value(char **split, int i, int *color);
int				check_color_info(char *line);
/**
 * store_map.c
 */
void			dup_map(t_info *info);
int				get_map_info(t_info *info);
/**
 * store_map_info.c
 */
void			store_info(t_info *info, int i, int j);
/**
 * key_event.c
 */
int				key_pressed(int keycode, t_info *info);
int				key_released(int keycode, t_info *info);
int				close_button(t_info *info);
/**
 * move.c
 */
void			player_move(t_info *info);

/**
 * util.c
 */
unsigned int	get_color(int *rgb);
void			my_mlx_pixel_put(t_info *data, \
								int x, int y, unsigned int color);
int				ft_splitlen(char **str);
void			free_double_char_ary(char **line);
int				check_extension(char *filename, char *extension);
/**
 * init_calc.c
 */
void			start_ray(t_info *info, t_calc *calc, int x);
void			init_dda(t_info *info, t_calc *calc);
/**
 * calc.c
 */
void			draw(t_info *info);
/**
 * main.c
 */
void			free_double_ptr(void **ptr, int size);
void			deinitialize(t_info *info);
/*
 * error_util.c
*/
void			error_exit(char *error);
void			system_error(char *errorMsg);
int				error_return(char *errorMsg);
#endif
