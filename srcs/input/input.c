/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:41:39 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 18:21:56 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_hook(game);
	else if ((keycode >= 0 && keycode < 256) || keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->keys[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if ((keycode >= 0 && keycode < 256) || keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->keys[keycode] = 0;
	return (0);
}

int exit_hook(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
void	handle_keys(t_game *game)
{
	if (game->keys[KEY_W])
		move_forward(game);
	if (game->keys[KEY_S])
		move_backward(game);
	if (game->keys[KEY_A])
		strafe_left(game);
	if (game->keys[KEY_D])
		strafe_right(game);
	if (game->keys[KEY_LEFT])
		rotate_left(game);
	if (game->keys[KEY_RIGHT])
		rotate_right(game);
}
