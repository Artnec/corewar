/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefunct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:06:01 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:06:04 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void			prefunct_for_big_d(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_litoa_base(p->temp_st, 10);
	}
	else if (p->j_on)
	{
		p->temp_im = va_arg(p->ap, intmax_t);
		p->temp_s = ft_litoa_base(p->temp_im, 10);
	}
	else if (p->l_on > 1)
	{
		p->temp_ld = va_arg(p->ap, long long);
		p->temp_s = ft_litoa_base(p->temp_ld, 10);
	}
	else
	{
		p->temp_ld = va_arg(p->ap, long);
		p->temp_s = ft_litoa_base(p->temp_ld, 10);
	}
	funct_for_d(p);
}

static void		prefunct_for_d2(t_p *p)
{
	if (p->l_on > 1)
	{
		p->temp_ld = va_arg(p->ap, long long);
		p->temp_s = ft_litoa_base(p->temp_ld, 10);
	}
	else if (p->h_on == 1)
	{
		p->temp_d = (short)va_arg(p->ap, int);
		p->temp_s = ft_itoa_base(p->temp_d, 10);
	}
	else if (p->h_on > 1)
	{
		p->temp_d = (signed char)va_arg(p->ap, int);
		p->temp_s = ft_itoa_base(p->temp_d, 10);
	}
	else
	{
		p->temp_d = va_arg(p->ap, int);
		p->temp_s = ft_itoa_base(p->temp_d, 10);
	}
	funct_for_d(p);
}

void			prefunct_for_d(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_litoa_base(p->temp_st, 10);
		funct_for_d(p);
	}
	else if (p->j_on)
	{
		p->temp_im = va_arg(p->ap, intmax_t);
		p->temp_s = ft_litoa_base(p->temp_im, 10);
		funct_for_d(p);
	}
	else if (p->l_on == 1)
	{
		p->temp_ld = va_arg(p->ap, long);
		p->temp_s = ft_litoa_base(p->temp_ld, 10);
		funct_for_d(p);
	}
	else
		prefunct_for_d2(p);
}

void			prefunct_for_big_u(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_ulxtoa_base(p->temp_st, 10);
	}
	else if (p->j_on)
	{
		p->temp_um = va_arg(p->ap, uintmax_t);
		p->temp_s = ft_ulxtoa_base(p->temp_um, 10);
	}
	else if (p->l_on > 1)
	{
		p->temp_ull = va_arg(p->ap, unsigned long long);
		p->temp_s = ft_ulxtoa_base(p->temp_ull, 10);
	}
	else
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_ulxtoa_base(p->temp_ul, 10);
	}
	funct_for_u(p);
}

void			prefunct_for_wc(t_p *p)
{
	p->temp_wc = va_arg(p->ap, wint_t);
	if (p->prec_found && p->precision < 0)
		p->width = ft_abs(p->precision);
	p->awd = check_the_width(p);
	(p->width - p->awd) < 0 ? (p->width = 0) : (p->width -= p->awd);
	while (p->width && !p->minus_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	funct_for_wc(p);
	while (p->width && p->minus_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
}
