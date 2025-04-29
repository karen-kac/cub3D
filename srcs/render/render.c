/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:41:21 by myokono           #+#    #+#             */
/*   Updated: 2025/04/27 19:39:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* レンダリング関数 */
int render(t_game *game)
{
    /* キー処理 */
    handle_keys(game);
    
    /* 背景描画 */
    render_background(game);
    
    /* レイキャスティング */
    raycasting(game);
    
    /* イメージをウィンドウに描画 */
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    
    return (0);
}

/* 背景描画（床と天井） */
void render_background(t_game *game)
{
    int x, y;
    
    /* 天井の描画 */
    for (y = 0; y < WINDOW_HEIGHT / 2; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
            put_pixel(&game->img, x, y, game->ceiling_color);
    }
    
    /* 床の描画 */
    for (y = WINDOW_HEIGHT / 2; y < WINDOW_HEIGHT; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
            put_pixel(&game->img, x, y, game->floor_color);
    }
}

/* ピクセル描画 */
void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;
    
    /* 境界チェック */
    if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
        return;
    
    /* ピクセルアドレス計算 */
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

/* テクスチャの色を取得 */
int get_tex_color(t_img *img, int x, int y)
{
    char *dst;
    
    /* 境界チェック */
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return (0);
    
    /* ピクセルアドレス計算 */
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}
