/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:31:08 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:11:45 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_map_data(t_game *game, char **map_lines, int height)
{
	int	max_width;
	int	i;
	int	j;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		if (strlen(map_lines[i]) > (size_t)max_width)
			max_width = strlen(map_lines[i]);
		i++;
	}
	game->map.grid = malloc(sizeof(char *) * (height + 1));
	if (!game->map.grid)
		return (error_msg(ERR_MEMORY));
	i = 0;
	while (i < height)
	{
		game->map.grid[i] = malloc(sizeof(char) * (max_width + 1));
		if (!game->map.grid[i])
		{
			j  = 0;
			while (j < i)
			{
				free(game->map.grid[j]);
				game->map.grid[j] = NULL;
				j++;
			}
			free(game->map.grid);
			game->map.grid = NULL;
			return (error_msg(ERR_MEMORY));
		}
		j = 0;
		while (j < max_width)
		{
			if ((size_t)j < strlen(map_lines[i]))
				game->map.grid[i][j] = map_lines[i][j];
			else
				game->map.grid[i][j] = ' ';
			j++;
		}
		game->map.grid[i][max_width] = '\0';
		i++;
	}
	game->map.grid[height] = NULL;
	game->map.width = max_width;
	game->map.height = height;
	return (1);
}
