/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:46:37 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/03 18:46:39 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	k;
	size_t	count;

	n = 0;
	while (dst[n] && dstsize)
		n++;
	if (dstsize > n)
		k = ft_strlen(dst) + ft_strlen(src);
	else
		k = ft_strlen(src) + dstsize;
	count = k;
	if (dstsize == 0)
		return (count);
	k = 0;
	while (n < dstsize - 1)
		dst[n++] = src[k++];
	dst[n] = 0;
	return (count);
}
