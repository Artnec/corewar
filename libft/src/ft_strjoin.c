/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:09:58 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/10 17:09:59 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	conc = (char*)malloc(sizeof(*conc) * (len + 1));
	if (!conc)
		return (0);
	i = 0;
	while (*s1)
	{
		conc[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		conc[i] = *s2;
		i++;
		s2++;
	}
	conc[i] = '\0';
	return (conc);
}
