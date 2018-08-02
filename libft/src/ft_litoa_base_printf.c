/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:15:10 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/10 16:15:11 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		create_res(intmax_t value, unsigned int base, char *res,
	int len)
{
	if (value < 0)
	{
		res[len--] = 56;
		value = 922337203685477580;
	}
	while (len)
	{
		if (value % base > 9)
			res[len] = (value % base) + 55;
		else
			res[len] = (value % base) + 48;
		len--;
		value /= base;
	}
	if (!res[len])
	{
		if (value % base > 9)
			res[len] = (value % base) + 55;
		else
			res[len] = (value % base) + 48;
	}
}

static int		base_count(intmax_t value, unsigned int base, int len)
{
	if (value < 0)
	{
		len = 19;
		return (len);
	}
	while (value > base - 1)
	{
		len++;
		value /= base;
	}
	return (len + 1);
}

char			*ft_litoa_base(intmax_t value, int base)
{
	char			*res;
	int				len;
	int				neg;

	if (!(base > 1 && base < 17))
		return (0);
	len = 0;
	neg = 0;
	if (value < 0)
	{
		neg = 1;
		value = -value;
	}
	len = base_count(value, base, len);
	if (base == 10 && neg == 1)
		len++;
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	res[0] = 0;
	res[len] = 0;
	if (base == 10 && neg == 1)
		res[0] = '-';
	create_res(value, base, res, (len - 1));
	return (res);
}
