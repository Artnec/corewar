/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:04:46 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:04:47 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	l;
	char	t;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	l = 0;
	while (i >= l)
	{
		t = str[i];
		str[i] = str[l];
		str[l] = t;
		i--;
		l++;
	}
	return (str);
}
