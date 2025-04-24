/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:39:16 by myokono           #+#    #+#             */
/*   Updated: 2023/09/24 18:32:58 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	to_copy;
	size_t	i;

	slen = ft_strlen(src);
	i = 0;
	if (dst == NULL && size == 0)
		return (slen);
	dlen = ft_strlen(dst);
	if (dlen < size)
	{
		to_copy = size - dlen - 1;
		if (slen < to_copy)
			to_copy = slen;
		while (i < to_copy)
		{
			dst[dlen + i] = src[i];
			i++;
		}
		dst[dlen + to_copy] = '\0';
		return (slen + dlen);
	}
	return (slen + size);
}
