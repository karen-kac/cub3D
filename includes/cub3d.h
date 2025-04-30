/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryabuki <ryabuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:37:41 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 11:44:43 by ryabuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../srcs/minilibx-linux/mlx.h"
# include "../srcs/libft/libft.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define TITLE "cub3D"

/* key */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* X11 event */
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_EXIT 17

/* direction */
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

/* error */
# define ERR_ARGS "Error\nInvalid arguments. Usage: ./cub3D [map.cub]"
# define ERR_FILE "Error\nCould not open file."
# define ERR_MAP "Error\nInvalid map."
# define ERR_CONFIG "Error\nInvalid configuration."
# define ERR_TEXTURE "Error\nCould not load texture."
# define ERR_MEMORY "Error\nMemory allocation failed."

/* motion */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* image */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* texture */
typedef struct s_tex
{
	t_img	img;
	char	*path;
}	t_tex;

/* player */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* raycast */
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	tex_pos;
	double	tex_step;
}	t_ray;

/* map */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

/* game */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_tex		tex[4];
	t_player	player;
	t_ray		ray;
	t_map		map;
	int			floor_color;
	int			ceiling_color;
	int			keys[70000];
}	t_game;

/* init */
void	init_game(t_game *game);
void	init_player(t_game *game);
bool	init_mlx(t_game *game);
bool	load_textures(t_game *game);

/* parse */
bool	parse_map(t_game *game, char *filename);
bool	parse_config(t_game *game, int fd);
int		check_map(t_game *game);
int		is_player(char c);
int		find_player(t_game *game);
int		convert_map_data(t_game *game, char **map_lines, int height);

/* raycasting */
void	raycasting(t_game *game);

/* render */
int		render(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);
/* input */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		exit_hook(t_game *game);
void	handle_keys(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

/* clean */
void	cleanup_game(t_game *game);
void	free_map(t_map *map);
void	free_textures(t_game *game);

/* utils */
bool	error_msg(char *msg);
void	free_split(char **split);
int		rgb_to_int(int r, int g, int b);
int		get_next_line(int fd, char **line);
bool	is_valid_extension(char *filename, char *ext);

#endif
