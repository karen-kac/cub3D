/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:38:01 by myokono           #+#    #+#             */
/*   Updated: 2025/04/23 10:58:06 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_valid_extension(char *filename, char *ext)
{
	int	filename_len;
	int	ext_len;

	if (!filename || !ext)
		return (false);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename_len <= ext_len)
		return (false);
	if (ft_strncmp(filename + filename_len - ext_len, ext, ext_len) != 0)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg(ERR_ARGS));
	if (is_valid_extension(argv[1], ".cub") == false)
		return (error_msg(ERR_FILE));
	init_game(&game);
	if (!parse_map(&game, argv[1]))
		return (cleanup_game(&game), 1);
	if (!init_mlx(&game))
		return (cleanup_game(&game), 1);
	init_player(&game);
	if (!load_textures(&game))
		return (cleanup_game(&game), 1);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1L<<0, key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 1L<<1, key_release, &game);
	mlx_hook(game.win, X_EVENT_EXIT, 1L<<17, exit_hook, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
