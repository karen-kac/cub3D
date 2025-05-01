/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:39:37 by myokono           #+#    #+#             */
/*   Updated: 2025/05/01 12:58:38 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	parse_texture(t_game *game, char *line, int dir)
{
	char	*path;

	while (*line == ' ')
		line++;
	path = ft_strdup(line);
	if (path == NULL)
		return (error_msg(ERR_MEMORY));
	if (game->tex[dir].path)
	{
		free(game->tex[dir].path);
		game->tex[dir].path = NULL;
	}
	game->tex[dir].path = path;
	return (true);
}

static bool	parse_color(t_game *game, char *line, char type)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (rgb == NULL)
		return (error_msg(ERR_MEMORY));
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(&rgb), error_msg(ERR_CONFIG));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(&rgb), error_msg(ERR_CONFIG));
	if (type == 'F')
		game->floor_color = rgb_to_int(r, g, b);
	else if (type == 'C')
		game->ceiling_color = rgb_to_int(r, g, b);
	free_split(&rgb);
	return (true);
}

static bool	parse_config_line(t_game *game, char *line)
{
	if (strncmp(line, "NO ", 3) == 0)
		return (parse_texture(game, line + 3, NORTH));
	else if (strncmp(line, "SO ", 3) == 0)
		return (parse_texture(game, line + 3, SOUTH));
	else if (strncmp(line, "WE ", 3) == 0)
		return (parse_texture(game, line + 3, WEST));
	else if (strncmp(line, "EA ", 3) == 0)
		return (parse_texture(game, line + 3, EAST));
	else if (strncmp(line, "F ", 2) == 0)
		return (parse_color(game, line + 2, 'F'));
	else if (strncmp(line, "C ", 2) == 0)
		return (parse_color(game, line + 2, 'C'));
	return (false);
}

bool	parse_config(t_game *game, int fd, int count)
{
	char	*line;
	int		ret;

	while (count < 6)
	{
		ret = get_next_line(fd, &line);
		if (ret <= 0)
		{
			if (line)
				free(line);
			return (error_msg(ERR_CONFIG));
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		ret = parse_config_line(game, line);
		free(line);
		if (ret == false)
			return (error_msg(ERR_CONFIG));
		count++;
	}
	return (true);
}
