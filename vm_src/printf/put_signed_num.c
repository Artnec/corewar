/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_signed_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:48:10 by anesteru          #+#    #+#             */
/*   Updated: 2018/01/23 15:48:12 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	recursive_put_num(unsigned long long num)
{
	if (num >= 10)
		recursive_put_num(num / 10);
	num = num % 10 + '0';
	write(1, &num, 1);
}

static int	put_num(long long num, unsigned long long n, int len, t_flags sd)
{
	int ret;
	int t;

	ret = (num < 0 || (num >= 0 && sd.plus == 1)) ? 1 : 0;
	t = (len > sd.precision) ? len : sd.precision;
	ret += (sd.space == 1 && num >= 0) ? write(1, " ", 1) : 0;
	if (sd.minus == 0 && (sd.zero == 0 || sd.precision != -1))
		while (sd.width - ret > t)
			ret += write(1, " ", 1);
	(num < 0) ? write(1, "-", 1) : 0;
	(num >= 0 && sd.plus == 1) ? write(1, "+", 1) : 0;
	if (sd.zero == 1)
		while (sd.width - ret > t)
			ret += write(1, "0", 1);
	while (sd.precision > len)
	{
		ret += write(1, "0", 1);
		sd.precision--;
	}
	if (num != 0 || sd.precision != 0)
		recursive_put_num(n);
	if (sd.minus == 1 && sd.width > ret + len)
		while (sd.width > ret + len)
			ret += write(1, " ", 1);
	return (ret);
}

static int	put_signed(long long num, t_flags *sd)
{
	int					ret;
	int					l;
	unsigned long long	n;

	n = num;
	if (num < 0)
		n = -num;
	l = num_len(num < 0 ? -num : num, 10, sd->precision);
	ret = put_num(num, n, l, *sd);
	return (ret + l);
}

int			put_signed_num(t_flags *sd, va_list argp)
{
	int ret;

	ret = 0;
	if (sd->type == 'D')
		ret = put_signed(va_arg(argp, long), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 0)
		ret = put_signed(va_arg(argp, int), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 1)
		ret = put_signed((char)va_arg(argp, int), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 2)
		ret = put_signed((short)va_arg(argp, int), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 3)
		ret = put_signed(va_arg(argp, long), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 4)
		ret = put_signed(va_arg(argp, long long), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 5)
		ret = put_signed(va_arg(argp, intmax_t), sd);
	else if ((sd->type == 'i' || sd->type == 'd') && sd->length == 6)
		ret = put_signed(va_arg(argp, size_t), sd);
	return (ret);
}
