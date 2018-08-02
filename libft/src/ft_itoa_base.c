/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:26:07 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/19 14:26:08 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		create_res(unsigned int value, unsigned int base, char *res,
	int len)
{
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

static int		base_count(unsigned int value, unsigned int base, int len)
{
	while (value > base - 1)
	{
		len++;
		value /= base;
	}
	return (len + 1);
}

char			*ft_itoa_base(int value, int base)
{
	char			*res;
	unsigned int	nb;
	int				len;
	int				neg;

	if (!(base > 1 && base < 17))
		return (0);
	nb = (unsigned int)value;
	len = 0;
	neg = 0;
	if (value < 0)
	{
		neg = 1;
		nb = (unsigned int)-value;
	}
	len = base_count(nb, base, len);
	if (base == 10 && neg == 1)
		len++;
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	res[len] = 0;
	res[0] = (base == 10 && neg == 1 ? '-' : 0);
	create_res(nb, base, res, (len - 1));
	return (res);
}
