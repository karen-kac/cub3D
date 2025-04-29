/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:51:43 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:19:13 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player(c));
}

static int	is_at_map_edge(t_game *game, int x, int y)
{
	return (x == 0 || y == 0
		|| x == game->map.width - 1 || y == game->map.height - 1);
}

static int	has_space_around(t_game *game, int x, int y)
{
	if (game->map.grid[y - 1][x] == ' ' || game->map.grid[y + 1][x] == ' ' ||
		game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	check_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (!is_valid_map_char(c))
				return (error_msg(ERR_MAP));
			if (c == '0' || is_player(c))
			{
				if (is_at_map_edge(game, x, y) || has_space_around(game, x, y))
					return (error_msg(ERR_MAP));
			}
			x++;
		}
		y++;
	}
	return (1);
}
