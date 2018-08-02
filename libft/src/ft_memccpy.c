/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:58:19 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/10/27 13:58:20 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;
	size_t			i;
	unsigned char	x;

	destination = (unsigned char*)dst;
	source = (unsigned char*)src;
	x = (unsigned char)c;
	i = n;
	while (i-- > 0)
	{
		if ((*destination++ = *source++) == x)
			return (destination);
	}
	return (NULL);
}
