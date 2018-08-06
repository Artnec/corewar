/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 15:14:09 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/04 15:14:10 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char **str, va_list argp)
{
	long	res;
	int		precision;

	res = 0;
	if (**str == '.')
		*str += 1;
	if (**str == '*')
	{
		precision = va_arg(argp, int);
		if (precision < 0)
			precision = -1;
		return (precision);
	}
	while (**str >= '0' && **str <= '9')
	{
		res = (res * 10) + **str - '0';
		*str += 1;
	}
	*str -= 1;
	return (res);
}

int		is_type(const char *s)
{
	return (*s == 'c' || *s == 'C' || *s == 's' || *s == 'S' || *s == 'i' ||
		*s == 'd' || *s == 'D' || *s == 'u' || *s == 'U' || *s == 'x' ||
		*s == 'X' || *s == 'p' || *s == 'o' || *s == 'O' || *s == 'b');
}

void	initialize_structure(t_flags *sd)
{
	sd->width = 0;
	sd->precision = -1;
	sd->minus = 0;
	sd->type = 0;
	sd->hash = 0;
	sd->space = 0;
	sd->zero = 0;
	sd->plus = 0;
	sd->length = 0;
	sd->wc = 0;
	sd->error = 0;
}

int		num_len(size_t num, unsigned int base, int precision)
{
	int	i;

	i = (precision == 0 && num == 0) ? 0 : 1;
	while (num /= base)
		i++;
	return (i);
}

int		put_space_or_zero(int width, int zero)
{
	int	i;

	i = -1;
	if (zero == 0)
		while (++i < width)
			write(1, " ", 1);
	else
		while (++i < width)
			write(1, "0", 1);
	return (i);
}
