/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:54:04 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/10/27 14:54:05 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	int					j;
	unsigned char		*destination;
	const unsigned char	*source;

	i = 0;
	j = len - 1;
	destination = (unsigned char*)dst;
	source = (const unsigned char*)src;
	if (dst > src)
	{
		while (j >= 0)
		{
			destination[j] = source[j];
			j--;
		}
		return (destination);
	}
	while (i < len)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}
