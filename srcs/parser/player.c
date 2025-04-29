/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:58:40 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 15:59:18 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
				if (player_found)
					return (error_msg(ERR_MAP));
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.grid[i][j];
				game->map.grid[i][j] = '0';
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (error_msg(ERR_MAP));
	return (1);
}
