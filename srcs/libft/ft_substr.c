/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:04:00 by myokono           #+#    #+#             */
/*   Updated: 2023/09/29 13:11:09 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_size;
	size_t	mal_size;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start >= s_size || len == 0)
		return (ft_strdup(""));
	if (s_size - start < len)
		mal_size = s_size - start;
	if (s_size - start >= len)
		mal_size = len;
	substr = (char *)malloc(sizeof(char) * (mal_size + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, mal_size + 1);
	return (substr);
}
