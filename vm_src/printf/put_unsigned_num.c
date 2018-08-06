/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsigned_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:57:00 by anesteru          #+#    #+#             */
/*   Updated: 2018/01/29 15:57:01 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	recursive_put_unsigned(size_t num, unsigned int base, int t)
{
	if (num >= base)
		recursive_put_unsigned(num / base, base, t);
	if (num % base > 9 && (t == 'x' || t == 'p'))
		num = num % base + 87;
	else if (num % base > 9 && t == 'X')
		num = num % base + 55;
	else
		num = num % base + '0';
	write(1, &num, 1);
}

static int	is_prefix(size_t num, t_flags *sd)
{
	if ((sd->hash == 1 && (sd->type == 'x' || sd->type == 'X')
		&& num != 0) || sd->type == 'p')
		return (2);
	else if (sd->hash == 1 && (sd->type == 'o' || sd->type == 'O')
		&& (num != 0 || (num == 0 && sd->precision == 0)))
		return (1);
	return (0);
}

static int	put_space_prefix_zero(int len, size_t num, t_flags *sd)
{
	int ret;
	int t;
	int l;

	ret = 0;
	l = 0;
	t = (sd->precision > len) ? sd->precision : len;
	if (sd->minus == 0 && (sd->zero == 0 || sd->precision != -1))
	{
		t -= (is_prefix(num, sd) == 1 && sd->precision > len) ? 1 : 0;
		l = put_space_or_zero(sd->width - t - is_prefix(num, sd), 0);
	}
	if (is_prefix(num, sd) == 2 && sd->type == 'X')
		write(1, "0X", 2);
	else if (is_prefix(num, sd) == 2 && (sd->type == 'x' || sd->type == 'p'))
		write(1, "0x", 2);
	else if (is_prefix(num, sd) == 1)
		ret += write(1, "0", 1);
	if (sd->precision == -1 && sd->zero == 1)
		l = put_space_or_zero(sd->width - t - is_prefix(num, sd), 1);
	while (sd->precision > len + ret)
		ret += write(1, "0", 1);
	ret += (is_prefix(num, sd) == 2) ? 2 : 0;
	return (ret + l);
}

static int	put_unsigned(size_t num, t_flags *sd)
{
	unsigned int	base;
	int				ret;
	int				len;

	if (sd->type == 'o' || sd->type == 'O')
		base = 8;
	else if (sd->type == 'u' || sd->type == 'U')
		base = 10;
	else if (sd->type == 'x' || sd->type == 'X' || sd->type == 'p')
		base = 16;
	else
		base = 2;
	len = num_len(num, base, sd->precision);
	ret = put_space_prefix_zero(len, num, sd);
	if (num != 0 || sd->precision != 0)
		recursive_put_unsigned(num, base, sd->type);
	if (sd->minus == 1)
		ret += put_space_or_zero(sd->width - len - ret, 0);
	return (ret + len);
}

int			put_unsigned_num(t_flags *sd, va_list argp)
{
	int ret;

	if (sd->type == 'U' || sd->type == 'p' || sd->type == 'O')
		ret = put_unsigned(va_arg(argp, unsigned long), sd);
	else if (sd->length == 0)
		ret = put_unsigned(va_arg(argp, unsigned), sd);
	else if (sd->length == 1)
		ret = put_unsigned((unsigned char)va_arg(argp, unsigned), sd);
	else if (sd->length == 2)
		ret = put_unsigned((unsigned short)va_arg(argp, unsigned), sd);
	else if (sd->length == 3)
		ret = put_unsigned(va_arg(argp, unsigned long), sd);
	else if (sd->length == 4)
		ret = put_unsigned(va_arg(argp, unsigned long long), sd);
	else if (sd->length == 5)
		ret = put_unsigned(va_arg(argp, intmax_t), sd);
	else
		ret = put_unsigned(va_arg(argp, size_t), sd);
	return (ret);
}
