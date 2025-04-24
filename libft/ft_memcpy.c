/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:07:15 by myokono           #+#    #+#             */
/*   Updated: 2023/09/18 17:23:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	ptr = dest;
	i = 0;
	while (i < n)
	{
		*ptr++ = *(unsigned char *)src++;
		i++;
	}
	return (dest);
}
