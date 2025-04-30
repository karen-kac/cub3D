/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryabuki <ryabuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:42:03 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 10:34:49 by ryabuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_extension(char *filename, char *ext)
{
	int	filename_len;
	int	ext_len;

	if (!filename || !ext)
		return (false);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename_len <= ext_len)
		return (false);
	if (ft_strncmp(filename + filename_len - ext_len, ext, ext_len) != 0)
		return (false);
	return (true);
}

bool	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (false);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
