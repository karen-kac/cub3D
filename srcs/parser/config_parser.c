/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:39:37 by myokono           #+#    #+#             */
/*   Updated: 2025/04/27 19:45:50 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* 設定情報の解析 */
int parse_config(t_game *game, int fd)
{
    char *line;
    int ret;
    int count = 0;

    /* 必要な設定が揃うまで読み込み */
    while (count < 6)  /* NO, SO, WE, EA, F, C の6つ */
    {
        ret = get_next_line(fd, &line);
        if (ret <= 0)
        {
            if (line)
                free(line);
            return (error_msg(ERR_CONFIG));
        }

        /* 空行はスキップ */
        if (line[0] == '\0')
        {
            free(line);
            continue;
        }

        /* 設定行の解析 */
        if (strncmp(line, "NO ", 3) == 0)
            ret = parse_texture(game, line + 3, NORTH);
        else if (strncmp(line, "SO ", 3) == 0)
            ret = parse_texture(game, line + 3, SOUTH);
        else if (strncmp(line, "WE ", 3) == 0)
            ret = parse_texture(game, line + 3, WEST);
        else if (strncmp(line, "EA ", 3) == 0)
            ret = parse_texture(game, line + 3, EAST);
        else if (strncmp(line, "F ", 2) == 0)
            ret = parse_color(game, line + 2, 'F');
        else if (strncmp(line, "C ", 2) == 0)
            ret = parse_color(game, line + 2, 'C');
        else
            ret = 0;

        if (ret)
            count++;

        free(line);
        if (!ret)
            return (0);
    }

    return (1);
}

/* テクスチャパスの解析 */
int parse_texture(t_game *game, char *line, int dir)
{
    char *path;
    
    /* 先頭の空白をスキップ */
    while (*line == ' ')
        line++;
    
    /* パス文字列の複製 */
    path = ft_strdup(line);
    if (!path)
        return (printf("here5"), error_msg(ERR_MEMORY));
    
    /* すでにパスが設定されていたら解放 */
    if (game->tex[dir].path)
    {
        free(game->tex[dir].path);
        game->tex[dir].path = NULL;
    }
    
    /* パスを設定 */
    game->tex[dir].path = path;
    
    return (1);
}

/* 色の解析 */
int parse_color(t_game *game, char *line, char type)
{
    int r, g, b;
    char **rgb;
    
    /* 先頭の空白をスキップ */
    while (*line == ' ')
        line++;
    
    /* RGBを分割 */
    rgb = ft_split(line, ',');
    if (!rgb)
        return (printf("here4"), error_msg(ERR_MEMORY));
    
    /* RGB値の取得 */
    if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
    {
        free_split(rgb);
        return (error_msg(ERR_CONFIG));
    }
    
    /* RGB値の解析 */
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    
    /* RGB値の範囲チェック */
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_split(rgb);
        return (error_msg(ERR_CONFIG));
    }
    
    /* 色を設定 */
    if (type == 'F')
        game->floor_color = rgb_to_int(r, g, b);
    else if (type == 'C')
        game->ceiling_color = rgb_to_int(r, g, b);
    
    free_split(rgb);
    return (1);
}