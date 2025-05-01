/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:20:02 by myokono           #+#    #+#             */
/*   Updated: 2025/05/01 13:50:19 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	buffer;
	double	check_x;
	double	check_y;

	buffer = 0.1;
	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (new_x > game->player.pos_x)
		check_x = new_x + buffer;
	else
		check_x = new_x - buffer;
	if (game->map.grid[(int)game->player.pos_y][(int)check_x] != '1')
		game->player.pos_x = new_x;
	if (new_y > game->player.pos_y)
		check_y = new_y + buffer;
	else
		check_y = new_y - buffer;
	if (game->map.grid[(int)check_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	buffer;
	double	check_x;
	double	check_y;

	buffer = 0.1;
	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (new_x < game->player.pos_x)
		check_x = new_x - buffer;
	else
		check_x = new_x + buffer;
	if (game->map.grid[(int)game->player.pos_y][(int)check_x] != '1')
		game->player.pos_x = new_x;
	if (new_y < game->player.pos_y)
		check_y = new_y - buffer;
	else
		check_y = new_y + buffer;
	if (game->map.grid[(int)check_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	buffer;
	double	check_x;
	double	check_y;

	buffer = 0.1;
	new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;
	if (new_x > game->player.pos_x)
		check_x = new_x + buffer;
	else
		check_x = new_x - buffer;
	if (game->map.grid[(int)game->player.pos_y][(int)check_x] != '1')
		game->player.pos_x = new_x;
	if (new_y < game->player.pos_y)
		check_y = new_y - buffer;
	else
		check_y = new_y + buffer;
	if (game->map.grid[(int)check_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	buffer;
	double	check_x;
	double	check_y;

	buffer = 0.1;
	new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
	if (new_x < game->player.pos_x)
		check_x = new_x - buffer;
	else
		check_x = new_x + buffer;
	if (game->map.grid[(int)game->player.pos_y][(int)check_x] != '1')
		game->player.pos_x = new_x;
	if (new_y > game->player.pos_y)
		check_y = new_y + buffer;
	else
		check_y = new_y - buffer;
	if (game->map.grid[(int)check_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}
