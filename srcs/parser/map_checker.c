/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:51:43 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 15:52:05 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == '0' || is_player(game->map.grid[i][j]))
			{
				if (i == 0 || i == game->map.height - 1 || \
					j == 0 || j == game->map.width - 1)
					return (error_msg(ERR_MAP));
				if (game->map.grid[i-1][j] == ' ' || \
					game->map.grid[i+1][j] == ' ' || \
					game->map.grid[i][j-1] == ' ' || \
					game->map.grid[i][j+1] == ' ')
					return (error_msg(ERR_MAP));
			}
			if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1' && \
				game->map.grid[i][j] != ' ' && !is_player(game->map.grid[i][j]))
				return (error_msg(ERR_MAP));
			j++;
		}
		i++;
	}
	return (1);
}
