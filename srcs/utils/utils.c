/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:42:03 by myokono           #+#    #+#             */
/*   Updated: 2025/04/29 16:16:23 by myokono          ###   ########.fr       */
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

int	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
