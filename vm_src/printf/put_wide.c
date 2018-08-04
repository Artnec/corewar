/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:58:55 by anesteru          #+#    #+#             */
/*   Updated: 2018/01/23 15:58:58 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	wide_char_len(wchar_t wc, t_flags *sd)
{
	if (wc < 0 || wc > 1114111 || (wc > 55295 && wc < 57344))
	{
		sd->error = -1;
		return (-1);
	}
	else if (wc > 255 && MB_CUR_MAX == 1)
	{
		sd->error = -1;
		return (-1);
	}
	else if (wc < 128 || (wc < 256 && MB_CUR_MAX == 1))
		return (1);
	else if (wc < 2056)
		return (2);
	else if (wc < 65536)
		return (3);
	return (4);
}

static int	put_wide_char(wchar_t wc, t_flags *sd)
{
	char	wide[4];
	int		i;

	i = wide_char_len(wc, sd);
	if (i == 1)
		wide[0] = (char)wc;
	else if (i == 2)
		wide[0] = (wc >> 6) | 192;
	else if (i == 3)
		wide[0] = ((wc >> 12) & 15) | 224;
	else
	{
		wide[0] = ((wc >> 18) & 7) | 240;
		wide[1] = ((wc >> 12) & 63) | 128;
	}
	if (i > 1)
		wide[i - 1] = (wc & 63) | 128;
	if (i > 2)
		wide[i - 2] = ((wc >> 6) & 63) | 128;
	write(1, wide, i);
	return (i);
}

static int	get_width(wchar_t *wstr, t_flags *sd)
{
	int		i;
	int		n;
	int		tmp;

	i = -1;
	n = 0;
	if (sd->precision != -1)
	{
		while (wstr[++i] && n <= sd->precision - wide_char_len(wstr[i], sd))
		{
			if ((tmp = wide_char_len(wstr[i], sd)) == -1)
				return (-1);
			n += tmp;
		}
	}
	else
	{
		while (wstr[++i])
		{
			if ((tmp = wide_char_len(wstr[i], sd)) == -1)
				return (-1);
			n += tmp;
		}
	}
	return (n);
}

int			put_wide_char_space_zero(wchar_t wc, t_flags *sd)
{
	int		ret;

	ret = 0;
	if (wide_char_len(wc, sd) == -1)
		return (-1);
	if (sd->minus == 0 && sd->width != 0)
		ret = put_space_or_zero(sd->width - wide_char_len(wc, sd), sd->zero);
	ret += put_wide_char(wc, sd);
	if (sd->minus == 1 && sd->width != 0)
		ret += put_space_or_zero(sd->width - wide_char_len(wc, sd), sd->zero);
	return (ret);
}

int			put_wide_str(wchar_t *wstr, t_flags *sd)
{
	int		ret;
	int		n;
	int		i;

	ret = 0;
	i = 0;
	if (wstr == NULL)
		n = (sd->precision == -1 || sd->precision > 6) ? 6 : sd->precision;
	else if ((n = get_width(wstr, sd)) == -1)
		return (-1);
	if (sd->minus == 0 && sd->width != 0)
		ret = put_space_or_zero(sd->width - n, sd->zero);
	if (wstr != NULL)
		while (*wstr)
		{
			if (sd->precision != -1 && n == i)
				break ;
			i += put_wide_char(*wstr++, sd);
		}
	else
		i += write(1, "(null)", n);
	if (sd->minus == 1 && sd->width != 0)
		ret += put_space_or_zero(sd->width - n, sd->zero);
	return (ret + i);
}
