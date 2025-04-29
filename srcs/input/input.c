/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:41:39 by myokono           #+#    #+#             */
/*   Updated: 2025/04/27 19:39:16 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* キー押下イベント */
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        exit_hook(game);
    else if (keycode < 256)
        game->keys[keycode] = 1;
    return (0);
}

/* キー解放イベント */
int key_release(int keycode, t_game *game)
{
    if (keycode < 256)
        game->keys[keycode] = 0;
    return (0);
}

/* 終了イベント */
int exit_hook(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}

/* キー処理 */
void handle_keys(t_game *game)
{
    double old_dir_x;
    double old_plane_x;

    /* 前後移動処理 (W, S) */
    if (game->keys[KEY_W])
    {
        /* 次の位置が壁でないか確認 */
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

    /* 左右移動処理 (A, D) */
    if (game->keys[KEY_A])
    {
        /* 横方向の移動（プレイヤーの向きに垂直な方向） */
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

    /* 視点回転処理 (←, →) */
    if (game->keys[KEY_LEFT])
    {
        /* 右回転行列による回転 */
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
    if (game->keys[KEY_RIGHT])
    {
        /* 左回転行列による回転 */
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }
}