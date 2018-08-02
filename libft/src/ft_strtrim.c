/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:21:07 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/10 17:21:09 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char		*invalid(void)
{
	char	*cpy;

	if (!(cpy = (char*)malloc(sizeof(*cpy))))
		return (0);
	cpy[0] = '\0';
	return (cpy);
}

static char		*valid(char const *s, int start, int end)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char*)malloc(sizeof(*cpy) * (end - start + 2));
	if (!cpy)
		return (0);
	while (start <= end)
	{
		cpy[i] = s[start];
		i++;
		start++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char			*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	if (!s)
		return (0);
	while ((s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		&& s[start])
		start++;
	while (s[end])
		end++;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t' ||
		s[end] == '\0') && end != 0)
		end--;
	if (start > end)
		return (invalid());
	return (valid(s, start, end));
}
