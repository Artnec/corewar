/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:40:37 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 19:40:38 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**With '\0' being passed as second argument returns a 2d array with the first
**element presented as the string "\0".
*/

#include "../include/libft.h"

static int		strsize(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static t_list	*create(char const *s, char c, t_list *split, char *newstr)
{
	t_list	*start;
	int		i;

	start = split;
	while (*s)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		if (!*s)
			return (start);
		if (!(newstr = ft_strnew(strsize(s, c))))
			return (start);
		while (*s != c && *s)
			newstr[i++] = *s++;
		newstr[i] = '\0';
		if (!(split->next = ft_lstnew(newstr, ft_strlen(newstr))))
			return (start);
		split = split->next;
	}
	return (start);
}

static t_list	*valid(char const *s, char c)
{
	t_list	*split;
	t_list	*start;
	char	*newstr;
	int		i;

	i = 0;
	while (*s == c && *s)
		s++;
	if (!*s)
		return (0);
	if (!(newstr = ft_strnew(strsize(s, c))))
		return (0);
	while (*s != c && *s)
		newstr[i++] = *s++;
	newstr[i] = '\0';
	if (!(split = ft_lstnew(newstr, ft_strlen(newstr))))
	{
		free(newstr);
		return (0);
	}
	start = create(s, c, split, newstr);
	return (start);
}

t_list			*ft_lstsplit(char const *s, char c)
{
	if (!s || !c)
		return (0);
	return (valid(s, c));
}
