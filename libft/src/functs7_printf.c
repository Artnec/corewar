/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:07:12 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:07:13 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		funct_for_x4(t_p *p)
{
	check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + 2 * p->sharp_on) >
		(size_t)ft_abs(p->precision) && !p->kostyl1 && p->temp_s[0] != 48 ?
		(p->len + 2 * p->sharp_on) : ft_abs(p->precision));
	if (p->sharp_on && p->temp_s[0] != 48 && p->temp_s[0] != 0)
	{
		p->buf[p->ret++] = '0';
		p->buf[p->ret++] = (p->fmt[p->i] == 'x' ? 'x' : 'X');
	}
	while (p->precision >= 0 && (p->precision -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 48;
		p->precision--;
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		2 * p->sharp_on - (int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_x3(t_p *p)
{
	while ((p->precision - (int)p->len - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while (p->minus_on && (p->width - 2 * p->sharp_on -
		(ft_abs(p->precision) > (int)p->len ?
		(ft_abs(p->precision) - (int)p->len) : 0) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
}

static void		funct_for_x2(t_p *p)
{
	check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + 2 * p->sharp_on) >
		(size_t)p->width && p->len ?
		(p->len + 2 * p->sharp_on) : (p->width - p->kostyl1));
	while (!p->minus_on && !p->zero_on && (p->width - 2 * p->sharp_on -
		(ft_abs(p->precision) > (int)p->len ?
		(ft_abs(p->precision) - (int)p->len) : 0) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
	if (p->sharp_on && p->temp_s[0] != 48 && p->temp_s[0] != 0)
	{
		p->buf[p->ret++] = '0';
		p->buf[p->ret++] = (p->fmt[p->i] == 'x' ? 'x' : 'X');
	}
	while (!p->minus_on && p->zero_on && (p->width - 2 * p->sharp_on -
		(ft_abs(p->precision) > (int)p->len ?
		(ft_abs(p->precision) - (int)p->len) : 0) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 48;
		p->width--;
	}
	funct_for_x3(p);
}

void			funct_for_x(t_p *p)
{
	if (p->temp_s[0] == 48 && p->precision && p->width)
		p->kostyl1 = 1;
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->sharp_on && p->temp_s[0] == 48 && p->width)
		p->width += 2;
	if (p->width >= ft_abs(p->precision))
		funct_for_x2(p);
	else
		funct_for_x4(p);
	ft_strdel(&p->temp_s);
}
