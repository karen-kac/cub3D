/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 01:54:48 by myokono           #+#    #+#             */
/*   Updated: 2023/09/27 14:44:59 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	size_t	size;

	size = 1;
	while (n / 10)
	{
		size++;
		n /= 10;
	}
	if (n < 0)
		size++;
	return (size);
}

static char	*ft_cpy(size_t size, int n, char *str)
{
	while (n)
	{
		str[size--] = '0' + n % 10;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*str;

	size = ft_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == INT_MIN)
		{
			str[size--] = '8';
			n /= 10;
		}
		n = -n;
	}
	return (ft_cpy(size, n, str));
}
