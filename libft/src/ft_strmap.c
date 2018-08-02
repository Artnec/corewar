/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:13:12 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/10 16:13:13 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*news;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	news = (char*)malloc(sizeof(*news) * (ft_strlen(s) + 1));
	if (!news)
		return (NULL);
	while (s[i])
	{
		news[i] = f(s[i]);
		i++;
	}
	news[i] = '\0';
	return (news);
}
