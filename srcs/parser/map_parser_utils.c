/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:31:08 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:23:08 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(char **map_lines, int height)
{
	int		max_width;
	int		i;
	size_t	len;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		len = strlen(map_lines[i]);
		if ((int)len > max_width)
			max_width = (int)len;
		i++;
	}
	return (max_width);
}

static int	allocate_map_grid(t_game *game, int height)
{
	game->map.grid = malloc(sizeof(char *) * (height + 1));
	if (!game->map.grid)
		return (error_msg(ERR_MEMORY));
	return (1);
}

static void	fill_map_line(char *dst, char *src, int max_width)
{
	int		i;
	size_t	len;

	len = strlen(src);
	i = 0;
	while (i < max_width)
	{
		if ((size_t)i < len)
			dst[i] = src[i];
		else
			dst[i] = ' ';
		i++;
	}
	dst[max_width] = '\0';
}

static void	free_partial_grid(t_game *game, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(game->map.grid[i++]);
	free(game->map.grid);
	game->map.grid = NULL;
}

int	convert_map_data(t_game *game, char **map_lines, int height)
{
	int	max_width;
	int	i;

	max_width = get_max_width(map_lines, height);
	if (!allocate_map_grid(game, height))
		return (0);
	i = 0;
	while (i < height)
	{
		game->map.grid[i] = malloc(sizeof(char) * (max_width + 1));
		if (!game->map.grid[i])
		{
			free_partial_grid(game, i);
			return (error_msg(ERR_MEMORY));
		}
		fill_map_line(game->map.grid[i], map_lines[i], max_width);
		i++;
	}
	game->map.grid[height] = NULL;
	game->map.width = max_width;
	game->map.height = height;
	return (1);
}
