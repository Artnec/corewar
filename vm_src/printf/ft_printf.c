/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:02:06 by anesteru          #+#    #+#             */
/*   Updated: 2018/01/29 22:02:09 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_length_flag(const char *fmt, t_flags *sd)
{
	int ret;
	int h;
	int l;

	ret = 0;
	h = 0;
	l = 1;
	while (*fmt && is_type(fmt) == 0)
	{
		if (*fmt == 'h' && l == 1)
			h++;
		else if (*fmt == 'l')
			l++;
		else if (*fmt == 'j' && ret < 5)
			ret = 5;
		else if (*fmt == 'z')
			ret = 6;
		fmt++;
	}
	if (h > 0 && ret < 5 && l == 1)
		ret = h % 2 + 1;
	else if (l > 1 && ret < 5)
		ret = l % 2 + 3;
	sd->wc = (l > 1 && l % 2 == 0) ? 1 : 0;
	return (ret);
}

static void	parse_flags(const char **fmt, va_list argp, t_flags *sd)
{
	if (**fmt == '#')
		sd->hash = 1;
	else if (**fmt == ' ')
		sd->space = 1;
	else if (**fmt == '+')
		sd->plus = 1;
	else if (**fmt == '-')
		sd->minus = 1;
	else if (**fmt == '*')
		sd->width = va_arg(argp, int);
	else if (**fmt == '.')
		sd->precision = ft_atoi(fmt, argp);
	else if (**fmt == '0')
		sd->zero = 1;
	else if (**fmt >= '0' && **fmt <= '9')
		sd->width = ft_atoi(fmt, argp);
	if (sd->width < 0)
	{
		sd->width = -(sd->width);
		sd->minus = 1;
	}
}

static int	get_flags(const char **fmt, va_list argp, t_flags *sd)
{
	const char	*tmp = *fmt;

	sd->length = get_length_flag(tmp, sd);
	while (is_type(tmp) == 0 && *tmp)
		tmp++;
	while (**fmt != *tmp)
	{
		if (**fmt == '#' || **fmt == ' ' || **fmt == '+' || **fmt == '-' ||
			**fmt == '.' || **fmt == '*' || (**fmt >= '0' && **fmt <= '9'))
			parse_flags(fmt, argp, sd);
		else if (**fmt != 'l' && **fmt != 'h' && **fmt != 'z' && **fmt != 'j')
		{
			*fmt += put_no_type(fmt, sd);
			return (1);
		}
		*fmt += 1;
	}
	sd->type = **fmt;
	if (sd->plus == 1)
		sd->space = 0;
	if (sd->minus == 1)
		sd->zero = 0;
	return (0);
}

static int	parse(const char **fmt, t_flags *sd, va_list argp)
{
	int	ret;

	ret = 0;
	if (get_flags(fmt, argp, sd) != 0)
		return (sd->plus);
	if (sd->type == 'c' || sd->type == 'C' || sd->type == 's' ||
		sd->type == 'S')
		ret = put_str_char(argp, sd);
	else if (sd->type == 'd' || sd->type == 'i' || sd->type == 'D')
		ret = put_signed_num(sd, argp);
	else if (sd->type == 'u' || sd->type == 'U' || sd->type == 'x' ||
		sd->type == 'X' || sd->type == 'o' || sd->type == 'O' ||
		sd->type == 'p' || sd->type == 'b')
		ret = put_unsigned_num(sd, argp);
	return (ret);
}

int			ft_printf(const char *fmt, ...)
{
	int		ret;
	va_list	argp;
	t_flags	sd;

	ret = 0;
	if (!fmt)
		return (-1);
	va_start(argp, fmt);
	while (*fmt)
	{
		initialize_structure(&sd);
		if (*fmt == '%')
		{
			fmt++;
			ret += (*fmt == '%') ? write(1, "%", 1) : parse(&fmt, &sd, argp);
			if (sd.error == -1)
				return (-1);
		}
		else
			ret += (sd.error == 0) ? write(1, fmt, 1) : 0;
		fmt += (*fmt) ? 1 : 0;
	}
	va_end(argp);
	return ((sd.error == -1) ? -1 : ret);
}
