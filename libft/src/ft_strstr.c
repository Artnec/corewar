/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:38:14 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/04 13:38:16 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	j;

	while (*haystack && *needle)
	{
		if (*haystack == *needle)
		{
			j = 0;
			while (*(haystack + j) == *(needle + j) && *(needle + j))
				j++;
			if (!*(needle + j))
				return ((char*)haystack);
		}
		haystack++;
	}
	if (!*haystack && *needle)
		return (NULL);
	return ((char*)haystack);
}
