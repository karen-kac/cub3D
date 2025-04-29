/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:39:02 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 15:59:41 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_lines(char **lines, int height)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < height)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

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
		return (printf("here3"), error_msg(ERR_MEMORY));
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
			printf("here2");
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



int	parse_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	**map_lines;
	char	**new_map_lines;
	int		height;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(ERR_FILE));
	if (!parse_config(game, fd))
		return (close(fd), 0);
	map_lines = NULL;
	height = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		new_map_lines = malloc(sizeof(char *) * (height + 2));
		if (!new_map_lines)
		{
			free(line);
			close(fd);
			printf("here");
			return (error_msg(ERR_MEMORY));
		}
		i = 0;
		while (i < height)
		{
			new_map_lines[i] = map_lines[i];
			i++;
		}
		new_map_lines[height] = line;
		new_map_lines[height + 1] = NULL;
		free(map_lines);
		map_lines = new_map_lines;
		height++;
	}
	free(line);
	close(fd);
	if (height == 0)
		return (free(map_lines), error_msg(ERR_MAP));
	if (!convert_map_data(game, map_lines, height))
		return (free_map_lines(map_lines, height), 0);
	if (!check_map(game))
	{
		free_map_lines(map_lines, height);
		free_map(&game->map);
		return (0);
	}
	if (!find_player(game))
	{
		free_map_lines(map_lines, height);
		free_map(&game->map);
		return (0);
	}
	free_map_lines(map_lines, height);
	return (1);
}
