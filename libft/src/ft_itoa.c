/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:27:15 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/11 15:27:16 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char		*ft_valid(char *res, int n, int indicator, int i)
{
	res[i] = '\0';
	i--;
	if (n == -2147483648)
	{
		res[i] = 56;
		n = n / 10;
		i--;
	}
	if (indicator == 1)
		n = n * -1;
	while (n > 9)
	{
		res[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	if (indicator == 1)
	{
		res[i] = n + 48;
		i--;
		res[i] = '-';
	}
	else
		res[i] = n + 48;
	return (res);
}

char			*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		indicator;

	indicator = 0;
	if (n < 0)
		indicator = 1;
	i = ft_intlen(n);
	res = ft_strnew(i);
	if (!res)
		return (0);
	else
		return (ft_valid(res, n, indicator, i));
}
