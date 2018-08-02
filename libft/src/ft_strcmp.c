/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 16:00:52 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/04 16:00:53 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
		{
			if (!(*str1 >= 0 && *str1 <= 255) || !(*str2 >= 0 && *str2 <= 255))
				return (1);
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (0);
}
