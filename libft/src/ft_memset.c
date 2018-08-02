/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:35:22 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/10/26 16:35:25 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	s;

	str = (unsigned char*)b;
	i = 0;
	s = c;
	while (i < len)
	{
		str[i] = s;
		i++;
	}
	return (b);
}
