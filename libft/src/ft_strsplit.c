/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:43:10 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/11 13:43:11 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char		**free_split(char ***temp)
{
	int		i;
	char	**split;

	split = *temp;
	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
	return (0);
}

static int		wordcount(char const *s, char c)
{
	int		i;
	int		words;
	int		counter;

	i = 0;
	words = 0;
	if (c == '\0')
		return (1);
	while (s[i])
	{
		counter = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] && s[i] != c)
		{
			counter = 1;
			i++;
		}
		while (s[i] == c && s[i])
			i++;
		if (counter == 1)
			words++;
	}
	return (words);
}

static int		strsize(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char		**valid(char const *s, char c)
{
	char	**split;
	char	*newstr;
	int		words;
	int		i;
	int		n;

	i = 0;
	n = 0;
	words = wordcount(s, c);
	if (!(split = (char**)malloc(sizeof(*split) * (words + 1))))
		return (0);
	while (n < words)
	{
		while (*s == c && *s)
			s++;
		if (!(newstr = ft_strnew(strsize(s, c))))
			return (free_split(&split));
		while (*s != c && *s)
			newstr[i++] = *s++;
		newstr[i] = '\0';
		split[n++] = newstr;
		i = 0;
	}
	split[words] = 0;
	return (split);
}

char			**ft_strsplit(char const *s, char c)
{
	if (!s)
		return (0);
	return (valid(s, c));
}
