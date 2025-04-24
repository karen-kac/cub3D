/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:18:50 by myokono           #+#    #+#             */
/*   Updated: 2023/09/24 19:12:00 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;

	llen = ft_strlen(little);
	if (llen == 0)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (*big != '\0')
	{
		if (len < llen)
			break ;
		if (ft_strncmp(big, little, llen) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
