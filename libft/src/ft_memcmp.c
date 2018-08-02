/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:11:27 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/02 16:11:28 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*first;
	const unsigned char	*second;
	size_t				i;

	first = (const unsigned char*)s1;
	second = (const unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (first[i] != second[i])
		{
			if (!(first[i] >= 0 && first[i] <= 255) ||
				!(second[i] >= 0 && second[i] <= 255))
				return (255);
			return (first[i] - second[i]);
		}
		i++;
	}
	return (0);
}
