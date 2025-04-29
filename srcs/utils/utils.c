/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:42:03 by myokono           #+#    #+#             */
/*   Updated: 2025/04/27 19:39:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
