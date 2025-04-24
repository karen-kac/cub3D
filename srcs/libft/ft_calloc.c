/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:48:48 by myokono           #+#    #+#             */
/*   Updated: 2023/08/17 12:48:48 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void		*ptr;

	if (num == 0 || size == 0)
	{
		ptr = malloc(sizeof(char) * 1);
		if (ptr == 0)
			return (NULL);
		*((char *)ptr) = '\0';
		return (ptr);
	}
	if (size != 0 && num > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(num * size);
	if (ptr != NULL)
		ft_memset(ptr, 0, num * size);
	return (ptr);
}

// #include<stdio.h>
// int main (){
// 	void *p;
// 	void *q;
// 	p = ft_calloc(0, -5);
// 	q = calloc(0, -5);
// 	printf ("%p\n", p);
// 	printf ("%p\n", q);

// }
