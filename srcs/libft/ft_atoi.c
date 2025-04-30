/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:51:50 by myokono           #+#    #+#             */
/*   Updated: 2025/04/30 19:02:25 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_maxmini(long num, char c)
{
	if ((num > LONG_MAX / 10 && ft_isdigit(c) == 1)
		|| (num == LONG_MAX / 10 && c - '0' > LONG_MAX % 10))
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (sign == 1 && ft_maxmini(num, str[i]) == -1)
			return ((int)LONG_MAX);
		if (sign == -1 && ft_maxmini(num, str[i]) == -1)
			return ((int)LONG_MIN);
	}
	return ((int)num * sign);
}
