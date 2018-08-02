/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispresent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:32:04 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:32:05 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Returns "1" if the string s1 is present in the string s2 or 0 if not.
*/

int		ft_ispresent(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 == *s2)
			s1++;
		s2++;
	}
	if (!*s1)
		return (1);
	else
		return (0);
}
