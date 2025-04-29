/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:20:02 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 18:22:27 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x + game->player.dir_x * MOVE_SPEED)] != '1')
		game->player.pos_x += game->player.dir_x * MOVE_SPEED;
	if (game->map.grid[(int)(game->player.pos_y + game->player.dir_y * MOVE_SPEED)][(int)game->player.pos_x] != '1')
		game->player.pos_y += game->player.dir_y * MOVE_SPEED;
}

void	move_backward(t_game *game)
{
	if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x - game->player.dir_x * MOVE_SPEED)] != '1')
		game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
	if (game->map.grid[(int)(game->player.pos_y - game->player.dir_y * MOVE_SPEED)][(int)game->player.pos_x] != '1')
		game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
}

void	strafe_left(t_game *game)
{
	if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x + game->player.dir_y * MOVE_SPEED)] != '1')
		game->player.pos_x += game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)(game->player.pos_y - game->player.dir_x * MOVE_SPEED)][(int)game->player.pos_x] != '1')
		game->player.pos_y -= game->player.dir_x * MOVE_SPEED;
}

void	strafe_right(t_game *game)
{
	if (game->map.grid[(int)game->player.pos_y][(int)(game->player.pos_x - game->player.dir_y * MOVE_SPEED)] != '1')
		game->player.pos_x -= game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)(game->player.pos_y + game->player.dir_x * MOVE_SPEED)][(int)game->player.pos_x] != '1')
		game->player.pos_y += game->player.dir_x * MOVE_SPEED;
}
