/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:26:30 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 18:28:56 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray_direction(t_game *game, int x)
{
	game->ray.camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;
	game->ray.ray_dir_x = game->player.dir_x
		+ game->player.plane_x * game->ray.camera_x;
	game->ray.ray_dir_y = game->player.dir_y
		+ game->player.plane_y * game->ray.camera_x;
}

static void	set_map_position(t_game *game)
{
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
}

static void	set_delta_distance(t_game *game)
{
	if (game->ray.ray_dir_x == 0)
		game->ray.delta_dist_x = INFINITY_DIST;
	else
		game->ray.delta_dist_x = fabs(1.0 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_y = INFINITY_DIST;
	else
		game->ray.delta_dist_y = fabs(1.0 / game->ray.ray_dir_y);
}

static void	set_step_and_side_dist(t_game *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}

	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

static void	initialize_ray_state(t_game *game)
{
	game->ray.hit = 0;
	game->ray.side = 0;
}

void	calculate_ray(t_game *game, int x)
{
	set_ray_direction(game, x);
	set_map_position(game);
	set_delta_distance(game);
	set_step_and_side_dist(game);
	initialize_ray_state(game);
}
