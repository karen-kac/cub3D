/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:58:40 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:16:31 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	set_player_info(t_game *game, int x, int y, int *player_found)
{
	if (*player_found)
		return (error_msg(ERR_MAP));
	game->map.player_x = x;
	game->map.player_y = y;
	game->map.player_dir = game->map.grid[y][x];
	game->map.grid[y][x] = '0';
	*player_found = 1;
	return (1);
}

int	find_player(t_game *game)
{
	int	i;
	int	j;
	int	player_found;

	player_found = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (is_player(game->map.grid[i][j]))
			{
				if (!set_player_info(game, j, i, &player_found))
					return (0);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (error_msg(ERR_MAP));
	return (1);
}
