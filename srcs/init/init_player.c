/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:37:43 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:44:26 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_game *game, double dir_x, double dir_y)
{
	game->player.dir_x = dir_x;
	game->player.dir_y = dir_y;
}
static void	set_plane(t_game *game, double plane_x, double plane_y)
{
	game->player.plane_x = plane_x;
	game->player.plane_y = plane_y;
}

void	init_player(t_game *game)
{
	game->player.pos_x = game->map.player_x + 0.5;
	game->player.pos_y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N')
	{
		set_dir(game, 0, -1);
		set_plane(game, 0.66, 0);
	}
	else if (game->map.player_dir == 'S')
	{
		set_dir(game, 0, 1);
		set_plane(game, -0.66, 0);
	}
	else if (game->map.player_dir == 'E')
	{
		set_dir(game, 1, 0);
		set_plane(game, 0, 0.66);
	}
	else if (game->map.player_dir == 'W')
	{
		set_dir(game, -1, 0);
		set_plane(game, 0, -0.66);
	}
}
