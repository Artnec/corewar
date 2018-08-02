/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uixtoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:07:59 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/01 20:08:00 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		create_res(uintmax_t value, unsigned int base, char *res,
	int len)
{
	while (len >= 0)
	{
		if (value % base > 9)
			res[len] = (value % base) + 55;
		else
			res[len] = (value % base) + 48;
		len--;
		value /= base;
	}
}

static int		base_count(uintmax_t value, unsigned int base, int len)
{
	while (value > base - 1)
	{
		len++;
		value /= base;
	}
	return (len + 1);
}

char			*ft_uixtoa_base(uintmax_t value, int base)
{
	char			*res;
	int				len;

	if (!(base > 1 && base < 17))
		return (0);
	len = 0;
	len = base_count(value, base, len);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	res[0] = 0;
	res[len] = 0;
	create_res(value, base, res, (len - 1));
	return (res);
}
