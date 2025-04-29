/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:42:26 by myokono           #+#    #+#             */
/*   Updated: 2025/04/27 19:39:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* テクスチャ処理 */
/* 
 * 注: このファイルは実質的には必要ないかもしれませんが、
 * テクスチャ関連の処理を拡張したい場合のために用意しています。
 * 現在の実装では、テクスチャの読み込みはinit.cで、
 * テクスチャの描画はraycasting.cで行っています。
 */

/* テクスチャの検証 */
int validate_textures(t_game *game)
{
    int i;
    
    /* 全てのテクスチャパスが設定されているか */
    for (i = 0; i < 4; i++)
    {
        if (!game->tex[i].path)
            return (error_msg(ERR_CONFIG));
    }
    
    /* 床と天井の色が設定されているか */
    if (game->floor_color == -1 || game->ceiling_color == -1)
        return (error_msg(ERR_CONFIG));
    
    return (1);
}

/* XPMファイルの検証 */
int is_valid_xpm(char *path)
{
    int fd;
    
    /* ファイルが開けるか */
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    
    close(fd);
    
    /* 拡張子が.xpmか */
    return (is_valid_extension(path, ".xpm"));
}

/* テクスチャカラー処理 - サイド効果を適用 */
int apply_side_effect(int color, int side)
{
    /* 側面の場合は色を暗くする */
    if (side == 1)
        return ((color >> 1) & 8355711);  /* 半分の明るさ */
    
    return (color);
}