/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:38:23 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:34:24 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor_color = -1;
	game->ceiling_color = -1;
}

/* MLX初期化 */
int init_mlx(t_game *game)
{
	/* MLX接続初期化 */
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_msg(ERR_MEMORY));
	/* ウィンドウ作成 */
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (error_msg(ERR_MEMORY));
	}
	
	/* イメージ初期化 */
	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img.img)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		game->win = NULL;
		return (error_msg(ERR_MEMORY));
	}
	
	/* イメージデータ取得 */
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
									  &game->img.line_length, &game->img.endian);
	
	return (1);
}

/* プレイヤー初期化 */
void init_player(t_game *game)
{
	/* プレイヤーの座標 */
	game->player.pos_x = game->map.player_x + 0.5;
	game->player.pos_y = game->map.player_y + 0.5;
	
	/* プレイヤーの向き設定 */
	if (game->map.player_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

/* テクスチャ読み込み */
int load_textures(t_game *game)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		/* テクスチャ画像読み込み */
		game->tex[i].img.img = mlx_xpm_file_to_image(game->mlx, game->tex[i].path, 
													&game->tex[i].img.width, 
													&game->tex[i].img.height);
		if (!game->tex[i].img.img)
			return (error_msg(ERR_TEXTURE));
		
		/* テクスチャデータ取得 */
		game->tex[i].img.addr = mlx_get_data_addr(game->tex[i].img.img,
												 &game->tex[i].img.bits_per_pixel,
												 &game->tex[i].img.line_length,
												 &game->tex[i].img.endian);
	}
	
	return (1);
}