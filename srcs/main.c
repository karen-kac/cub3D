/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:38:01 by myokono           #+#    #+#             */
/*   Updated: 2025/05/01 12:39:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg(ERR_ARGS));
	if (is_valid_extension(argv[1], ".cub") == false)
		return (error_msg(ERR_FILE));
	init_game(&game);
	if (parse_map(&game, argv[1]) == false)
		return (cleanup_game(&game), EXIT_FAILURE);
	if (init_mlx(&game) == false)
		return (cleanup_game(&game), EXIT_FAILURE);
	init_player(&game);
	if (load_textures(&game) == false)
		return (cleanup_game(&game), EXIT_FAILURE);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1L << 0, key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 1L << 1, key_release, &game);
	mlx_hook(game.win, X_EVENT_EXIT, 1L << 17, exit_hook, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
