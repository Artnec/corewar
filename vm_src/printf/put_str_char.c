/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:52:21 by anesteru          #+#    #+#             */
/*   Updated: 2018/01/27 19:52:24 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_char(int c, t_flags sd)
{
	int	ret;

	ret = 1;
	if (sd.minus == 0 && sd.width > 1)
		ret += put_space_or_zero(sd.width - 1, sd.zero);
	write(1, &c, 1);
	if (sd.minus == 1 && sd.width > 1)
		ret += put_space_or_zero(sd.width - 1, sd.zero);
	return (ret);
}

static int	print_str(char *str, t_flags sd)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (str != NULL)
		while (str[i])
			i++;
	else
		i = 6;
	if (sd.precision != -1 && i > sd.precision)
		i = sd.precision;
	if (sd.minus == 0 && sd.width != 0)
		ret = put_space_or_zero(sd.width - i, sd.zero);
	(str == NULL) ? write(1, "(null)", i) : write(1, str, i);
	if (sd.minus == 1 && sd.width != 0)
		ret = put_space_or_zero(sd.width - i, sd.zero);
	return (i + ret);
}

int			put_str_char(va_list argp, t_flags *sd)
{
	int	ret;

	if ((sd->type == 'c' && sd->wc == 1) || sd->type == 'C')
		ret = put_wide_char_space_zero(va_arg(argp, wchar_t), sd);
	else if (sd->type == 'c')
		ret = print_char(va_arg(argp, int), *sd);
	else if ((sd->type == 's' && sd->wc == 1) || sd->type == 'S')
		ret = put_wide_str(va_arg(argp, wchar_t *), sd);
	else
		ret = print_str(va_arg(argp, char *), *sd);
	return (ret);
}

int			put_no_type(const char **fmt, t_flags *sd)
{
	int ret;
	int len;

	ret = 0;
	if (sd->minus == 0)
		len = put_space_or_zero(sd->width - 1, sd->zero) + 1;
	ret += write(1, *fmt, 1);
	if (sd->minus == 1)
		len = put_space_or_zero(sd->width - 1, 0) + 1;
	while (*(*fmt + ret) != '%' && *(*fmt + ret) != '\0')
		write(1, *fmt + ret++, 1);
	sd->plus = len + ret - 1;
	return (ret - 1);
}
