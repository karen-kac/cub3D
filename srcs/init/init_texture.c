/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:38:47 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:39:40 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->tex[i].img.img = mlx_xpm_file_to_image(game->mlx, game->tex[i].path, 
													&game->tex[i].img.width, 
													&game->tex[i].img.height);
		if (!game->tex[i].img.img)
			return (error_msg(ERR_TEXTURE));
		game->tex[i].img.addr = mlx_get_data_addr(game->tex[i].img.img,
												 &game->tex[i].img.bits_per_pixel,
												 &game->tex[i].img.line_length,
												 &game->tex[i].img.endian);
		i++;
	}
	return (1);
}
