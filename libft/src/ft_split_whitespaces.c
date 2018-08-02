/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:45:32 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:45:33 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**NOT protected
*/

#include "../include/libft.h"

static int		ft_wordcount(char *str)
{
	int i;
	int ind;
	int words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		ind = 0;
		while (SEP(str[i]) && str[i] != '\0')
			i++;
		while (!(SEP(str[i])) && str[i] != '\0')
		{
			i++;
			ind = 1;
		}
		while (SEP(str[i]) && str[i] != '\0')
			i++;
		if (ind == 1)
			words++;
	}
	return (words);
}

static int		newstr_size(char *str)
{
	int i;

	i = 0;
	while (SEP(str[i]) && str[i] != '\0')
		str++;
	while (!(SEP(str[i])) && str[i] != '\0')
		i++;
	return (i);
}

char			**ft_split_whitespaces(char *str)
{
	int		words;
	int		k;
	int		i;
	char	**array;
	char	*newstr;

	i = 0;
	k = 0;
	words = ft_wordcount(str);
	array = (char**)malloc(sizeof(char*) * (words + 1));
	while (k < words)
	{
		newstr = (char*)malloc(sizeof(char) * (newstr_size(str) + 1));
		while (SEP(str[0]) && str[0] != '\0')
			str++;
		while (!(SEP(str[0])) && str[0] != '\0')
			newstr[i++] = *str++;
		newstr[i] = '\0';
		if (!(array[k] = newstr))
			return (array);
		k++;
		i = 0;
	}
	array[words] = 0;
	return (array);
}
