/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:06:50 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:06:52 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		funct_for_d4(t_p *p)
{
	check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + p->kostyl4) >
		(size_t)ft_abs(p->precision) ?
		(p->len + p->kostyl4) : ft_abs(p->precision));
	if (p->plus_on && p->temp_s[0] != '-' && !p->zero_on)
		p->buf[p->ret++] = '+';
	while (p->precision >= 0 && (p->precision -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 48;
		p->precision--;
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		p->spaces - (p->minus_del ? 1 : p->plus_on) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_d3(t_p *p)
{
	while ((p->precision - (int)p->len - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while (p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)p->len ? (ft_abs(p->precision) -
		(int)p->len) : 0) - (p->prec_found || !p->precision ||
		p->temp_s[0] == 48 || (p->width > (int)p->len && p->prec_found) ?
		p->spaces : 0) - (p->temp_s[0] == '-' ? 0 : p->plus_on) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
}

static void		funct_for_d2(t_p *p)
{
	check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + p->kostyl3) >
		(size_t)ft_abs(p->width + p->kostyl1 - p->kostyl2 - p->kostyl3) ?
		(p->len + p->kostyl3) : (p->width + p->kostyl1 - p->kostyl2 -
		p->kostyl3));
	while (!p->minus_on && (p->width - (ft_abs(p->precision) > (int)p->len ?
		(ft_abs(p->precision) - (int)p->len) : 0) - (!p->prec_found ||
		p->prec_found || !p->precision || p->temp_s[0] == 48 || (p->width >
			(int)p->len && p->prec_found) ? p->spaces : 0) -
		(p->temp_s[0] == '-' ? 0 : p->plus_on) - (int)p->len) > 0)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	if (p->plus_on && p->temp_s[0] != '-' && !p->zero_on)
		p->buf[p->ret++] = '+';
	if (p->minus_del && p->precision <= p->width && p->precision > 0)
		p->buf[p->ret++] = '-';
	funct_for_d3(p);
}

static void		funct_for_d1(t_p *p)
{
	if (p->plus_on && p->temp_s[0] != '-' && p->zero_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '+';
	}
	if (p->spaces && !p->minus_del && p->temp_s[0] != '-')
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = 32;
	}
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
}

void			funct_for_d(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if ((p->temp_s[0] == '-' && p->prec_found) || (p->plus_on &&
		p->temp_s[0] != '-'))
		p->kostyl1 = 1;
	if ((p->plus_on && p->zero_on && p->temp_s[0] != '-') ||
		(p->spaces && p->temp_s[0] != '-'))
		p->kostyl2 = 1;
	if ((p->plus_on && p->temp_s[0] != '-') || (p->temp_s[0] == '-' &&
		p->width && p->width < (int)ft_strlen(p->temp_s)))
		p->kostyl3 = 1;
	if (p->plus_on && p->temp_s[0] != '-')
		p->kostyl4 = 1;
	if (p->temp_s[0] == '-' && ((p->width && p->zero_on) || p->prec_found))
		minus_del(p);
	if (p->spaces && p->minus_del)
		p->spaces = 0;
	funct_for_d1(p);
	if (p->width >= ft_abs(p->precision))
		funct_for_d2(p);
	else
		funct_for_d4(p);
	ft_strdel(&p->temp_s);
}
