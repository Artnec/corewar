/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:56:53 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/04 14:56:55 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*haystack && *needle && i < len)
	{
		if (*haystack == *needle)
		{
			j = 0;
			while (*(haystack + j) == *(needle + j) &&
				*(needle + j) && (i + j) < len)
				j++;
			if (!*(needle + j) && (i + j) < (len + 1))
				return ((char*)haystack);
		}
		haystack++;
		i++;
	}
	if ((!*haystack && *needle) || i == len || (i + j) == len)
		return (NULL);
	return ((char*)haystack);
}
