/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:40:24 by myokono           #+#    #+#             */
/*   Updated: 2025/04/27 19:39:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* レイキャスティングの実行 */
void raycasting(t_game *game)
{
    int x;
    
    for (x = 0; x < WINDOW_WIDTH; x++)
    {
        /* レイの計算 */
        calculate_ray(game, x);
        
        /* DDAアルゴリズムで壁を検出 */
        perform_dda(game);
        
        /* 壁までの距離を計算 */
        calculate_wall_distance(game);
        
        /* 壁の高さを計算 */
        calculate_wall_height(game);
        
        /* テクスチャX座標の計算 */
        calculate_texture_x(game);
        
        /* 壁の描画 */
        draw_wall(game, x);
    }
}

/* レイの計算 */
void calculate_ray(t_game *game, int x)
{
    /* カメラ平面上のX座標（-1.0〜1.0） */
    game->ray.camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;
    
    /* レイの方向ベクトル */
    game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x * game->ray.camera_x;
    game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y * game->ray.camera_x;
    
    /* マップ上の現在位置 */
    game->ray.map_x = (int)game->player.pos_x;
    game->ray.map_y = (int)game->player.pos_y;
    
    /* デルタ距離の計算 */
    if (game->ray.ray_dir_x == 0)
        game->ray.delta_dist_x = 1e30;  /* 無限大を避けるための大きな値 */
    else
        game->ray.delta_dist_x = fabs(1.0 / game->ray.ray_dir_x);
    
    if (game->ray.ray_dir_y == 0)
        game->ray.delta_dist_y = 1e30;
    else
        game->ray.delta_dist_y = fabs(1.0 / game->ray.ray_dir_y);
    
    /* ステップ方向とサイド距離の計算 */
    if (game->ray.ray_dir_x < 0)
    {
        game->ray.step_x = -1;
        game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x) * game->ray.delta_dist_x;
    }
    else
    {
        game->ray.step_x = 1;
        game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x) * game->ray.delta_dist_x;
    }
    
    if (game->ray.ray_dir_y < 0)
    {
        game->ray.step_y = -1;
        game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y) * game->ray.delta_dist_y;
    }
    else
    {
        game->ray.step_y = 1;
        game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y) * game->ray.delta_dist_y;
    }
    
    /* 初期化 */
    game->ray.hit = 0;
    game->ray.side = 0;
}

/* DDAアルゴリズムで壁を検出 */
void perform_dda(t_game *game)
{
    /* DDAアルゴリズム */
    while (game->ray.hit == 0)
    {
        /* 次のマップセルへ */
        if (game->ray.side_dist_x < game->ray.side_dist_y)
        {
            game->ray.side_dist_x += game->ray.delta_dist_x;
            game->ray.map_x += game->ray.step_x;
            game->ray.side = 0;  /* X方向の壁に当たった */
        }
        else
        {
            game->ray.side_dist_y += game->ray.delta_dist_y;
            game->ray.map_y += game->ray.step_y;
            game->ray.side = 1;  /* Y方向の壁に当たった */
        }
        
        /* 壁に当たったかチェック */
        if (game->ray.map_y >= 0 && game->ray.map_y < game->map.height &&
            game->ray.map_x >= 0 && game->ray.map_x < game->map.width &&
            game->map.grid[game->ray.map_y][game->ray.map_x] == '1')
            game->ray.hit = 1;
    }
}

/* 壁までの距離を計算 */
void calculate_wall_distance(t_game *game)
{
    /* 壁までの垂直距離を計算 */
    if (game->ray.side == 0)
        game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos_x + 
                                   (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
    else
        game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos_y + 
                                   (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
}

/* 壁の高さを計算 */
void calculate_wall_height(t_game *game)
{
    /* 壁の高さを計算 */
    game->ray.line_height = (int)(WINDOW_HEIGHT / game->ray.perp_wall_dist);
    
    /* 描画の開始位置と終了位置を計算 */
    game->ray.draw_start = -game->ray.line_height / 2 + WINDOW_HEIGHT / 2;
    if (game->ray.draw_start < 0)
        game->ray.draw_start = 0;
    
    game->ray.draw_end = game->ray.line_height / 2 + WINDOW_HEIGHT / 2;
    if (game->ray.draw_end >= WINDOW_HEIGHT)
        game->ray.draw_end = WINDOW_HEIGHT - 1;
    
    /* テクスチャ番号の決定 */
    if (game->ray.side == 0)
    {
        if (game->ray.ray_dir_x > 0)
            game->ray.tex_num = EAST;
        else
            game->ray.tex_num = WEST;
    }
    else
    {
        if (game->ray.ray_dir_y > 0)
            game->ray.tex_num = SOUTH;
        else
            game->ray.tex_num = NORTH;
    }
}

/* テクスチャX座標の計算 */
void calculate_texture_x(t_game *game)
{
    /* 壁の当たった位置を計算 */
    if (game->ray.side == 0)
        game->ray.wall_x = game->player.pos_y + game->ray.perp_wall_dist * game->ray.ray_dir_y;
    else
        game->ray.wall_x = game->player.pos_x + game->ray.perp_wall_dist * game->ray.ray_dir_x;
    game->ray.wall_x -= floor(game->ray.wall_x);
    
    /* テクスチャのX座標を計算 */
    game->ray.tex_x = (int)(game->ray.wall_x * (double)game->tex[game->ray.tex_num].img.width);
    if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
        game->ray.tex_x = game->tex[game->ray.tex_num].img.width - game->ray.tex_x - 1;
    if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
        game->ray.tex_x = game->tex[game->ray.tex_num].img.width - game->ray.tex_x - 1;
    
    /* テクスチャのY座標移動量を計算 */
    game->ray.tex_step = 1.0 * game->tex[game->ray.tex_num].img.height / game->ray.line_height;
    
    /* テクスチャの開始位置 */
    game->ray.tex_pos = (game->ray.draw_start - WINDOW_HEIGHT / 2 + game->ray.line_height / 2)
                        * game->ray.tex_step;
}

/* 壁の描画 */
void draw_wall(t_game *game, int x)
{
    int y;
    int tex_y;
    int color;
    
    /* 描画範囲を走査 */
    for (y = game->ray.draw_start; y < game->ray.draw_end; y++)
    {
        /* テクスチャのY座標 */
        tex_y = (int)game->ray.tex_pos & (game->tex[game->ray.tex_num].img.height - 1);
        game->ray.tex_pos += game->ray.tex_step;
        
        /* テクスチャの色を取得 */
        color = get_tex_color(&game->tex[game->ray.tex_num].img, game->ray.tex_x, tex_y);
        
        /* 側面の場合は色を暗くする */
        if (game->ray.side == 1)
            color = (color >> 1) & 8355711;
        
        /* ピクセルを描画 */
        put_pixel(&game->img, x, y, color);
    }
}