/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:36:48 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/03 19:36:50 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
	{
		while (i != 0)
		{
			s++;
			i--;
		}
		return ((char*)s);
	}
	while (*s)
	{
		if (*s == (char)c)
		{
			while (*s)
				s++;
			while (*s != (char)c)
				s--;
			return ((char*)s);
		}
		s++;
	}
	return (NULL);
}
