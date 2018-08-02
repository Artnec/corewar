/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:24:49 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/02 17:24:50 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tab;
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	tab = (char*)malloc(sizeof(*tab) * (i + 1));
	if (tab >= s1)
	{
		i = 0;
		while (s1[i])
		{
			tab[i] = s1[i];
			i++;
		}
		tab[i] = '\0';
		return (tab);
	}
	return (NULL);
}
