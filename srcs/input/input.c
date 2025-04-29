/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:41:39 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 17:34:48 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_hook(game);
	else if (keycode < 256)
		game->keys[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode < 256)
		game->keys[keycode] = 0;
	return (0);
}

int exit_hook(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void handle_keys(t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	if (game->keys[KEY_W])
	{
		if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x + game->player.dir_x * MOVE_SPEED)] != '1')
			game->player.pos_x += game->player.dir_x * MOVE_SPEED;
		if (game->map.grid[(int)(game->player.pos_y + game->player.dir_y * MOVE_SPEED)][(int)game->player.pos_x] != '1')
			game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys[KEY_S])
	{
		if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x - game->player.dir_x * MOVE_SPEED)] != '1')
			game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
		if (game->map.grid[(int)(game->player.pos_y - game->player.dir_y * MOVE_SPEED)][(int)game->player.pos_x] != '1')
			game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys[KEY_A])
	{
		if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x - game->player.dir_y * MOVE_SPEED)] != '1')
			game->player.pos_x -= game->player.dir_y * MOVE_SPEED;
		if (game->map.grid[(int)(game->player.pos_y + game->player.dir_x * MOVE_SPEED)][(int)game->player.pos_x] != '1')
			game->player.pos_y += game->player.dir_x * MOVE_SPEED;
	}
	if (game->keys[KEY_D])
	{
		if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x + game->player.dir_y * MOVE_SPEED)] != '1')
			game->player.pos_x += game->player.dir_y * MOVE_SPEED;
		if (game->map.grid[(int)(game->player.pos_y - game->player.dir_x * MOVE_SPEED)][(int)game->player.pos_x] != '1')
			game->player.pos_y -= game->player.dir_x * MOVE_SPEED;
	}
	if (game->keys[KEY_LEFT])
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
		game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
		game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
	}
	if (game->keys[KEY_RIGHT])
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
		game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
		game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
	}
}