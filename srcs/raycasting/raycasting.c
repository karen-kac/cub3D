/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:40:24 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 18:58:03 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perform_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->ray.map_y >= 0 && game->ray.map_y < game->map.height
			&&game->ray.map_x >= 0 && game->ray.map_x < game->map.width
			&&game->map.grid[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.hit = 1;
	}
}

void	calculate_texture_x(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.wall_x = game->player.pos_y
			+ game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->player.pos_x
			+ game->ray.perp_wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	game->ray.tex_x = (int)(game->ray.wall_x
			* (double)game->tex[game->ray.tex_num].img.width);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		game->ray.tex_x = game->tex[game->ray.tex_num].img.width
			- game->ray.tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		game->ray.tex_x = game->tex[game->ray.tex_num].img.width
			- game->ray.tex_x - 1;
	game->ray.tex_step = 1.0 * game->tex[game->ray.tex_num].img.height
		/ game->ray.line_height;
	game->ray.tex_pos = (game->ray.draw_start - WINDOW_HEIGHT / 2
			+ game->ray.line_height / 2)
		* game->ray.tex_step;
}

static int	get_tex_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*) dst);
}

static void	draw_wall(t_game *game, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		tex_y = (int)game->ray.tex_pos
			& (game->tex[game->ray.tex_num].img.height - 1);
		game->ray.tex_pos += game->ray.tex_step;
		color = get_tex_color(&game->tex[game->ray.tex_num].img,
				game->ray.tex_x, tex_y);
		if (game->ray.side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_ray(game, x);
		perform_dda(game);
		calculate_wall_distance(game);
		calculate_wall_height(game);
		calculate_texture_x(game);
		draw_wall(game, x);
		x++;
	}
}
