/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:34:39 by myokono           #+#    #+#             */
/*   Updated: 2025/04/25 18:43:46 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	get_next_line(int fd, char **line)
{
	int		ret;
	int		i;
	char	buffer[1024];

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	i = 0;
	while ((ret = read(fd, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
			break ;
		i++;
	}
	if (ret < 0)
		return (-1);
	if (i == 0 && ret == 0)
		return (0);
	buffer[i] = '\0';
	*line = ft_strdup(buffer);
	if (!*line)
		return (-1);
	return (1);
}
