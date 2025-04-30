/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:49:35 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 18:50:29 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_distance(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos_x
				+ (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos_y
				+ (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
}

void	calculate_wall_height(t_game *game)
{
	game->ray.line_height = (int)(WINDOW_HEIGHT / game->ray.perp_wall_dist);
	game->ray.draw_start = -game->ray.line_height / 2 + WINDOW_HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + WINDOW_HEIGHT / 2;
	if (game->ray.draw_end >= WINDOW_HEIGHT)
		game->ray.draw_end = WINDOW_HEIGHT - 1;
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			game->ray.tex_num = EAST;
		else
			game->ray.tex_num = WEST;
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			game->ray.tex_num = SOUTH;
		else
			game->ray.tex_num = NORTH;
	}
}
