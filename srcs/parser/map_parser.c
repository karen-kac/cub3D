/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryabuki <ryabuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:39:02 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 10:37:48 by ryabuki          ###   ########.fr       */
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

static int	read_map_lines(int fd, char ***map_lines, int *height)
{
	char	*line;
	char	**new_map_lines;
	int		i;

	*map_lines = NULL;
	*height = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		new_map_lines = malloc(sizeof(char *) * (*height + 2));
		if (!new_map_lines)
			return (free(line), error_msg(ERR_MEMORY));
		i = 0;
		while (i < *height)
		{
			new_map_lines[i] = (*map_lines)[i];
			i++;
		}
		new_map_lines[*height] = line;
		new_map_lines[*height + 1] = NULL;
		free(*map_lines);
		*map_lines = new_map_lines;
		(*height)++;
	}
	free(line);
	return (1);
}

bool	parse_map(t_game *game, char *filename)
{
	int		fd;
	char	**map_lines;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg(ERR_FILE));
	if (parse_config(game, fd) == false)
		return (close(fd), false);
	if (read_map_lines(fd, &map_lines, &height) == false)
		return (close(fd), false);
	close(fd);
	if (height == 0)
		return (free(map_lines), error_msg(ERR_MAP));
	if (!convert_map_data(game, map_lines, height))
		return (free_map_lines(map_lines, height), false);
	if (check_map(game) == false)
	{
		free_map_lines(map_lines, height);
		free_map(&game->map);
		return (false);
	}
	if (find_player(game) == false)
	{
		free_map_lines(map_lines, height);
		free_map(&game->map);
		return (false);
	}
	free_map_lines(map_lines, height);
	return (true);
}
