/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:07:07 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:07:08 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		funct_for_o4(t_p *p)
{
	check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + p->sharp_on) >
		(size_t)ft_abs(p->precision) && !p->kostyl1 ?
		(p->len + p->sharp_on) : ft_abs(p->precision));
	while (p->precision >= 0 && (p->precision - p->sharp_on -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 48;
		p->precision--;
	}
	if (p->sharp_on && ((p->prec_found && !p->dotnull) ||
		(!p->prec_found && p->temp_s[0] != 48)))
		p->buf[p->ret++] = '0';
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		p->sharp_on - (int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_o3(t_p *p)
{
	while (p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)p->len || p->temp_s[0] == 48 ? 0 : p->sharp_on) -
		(ft_abs(p->precision) > (int)p->len ?
		(ft_abs(p->precision) - (int)p->len) : 0) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
}

static void		funct_for_o2(t_p *p)
{
	check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + p->sharp_on) >
		(size_t)p->width ? (p->len + p->sharp_on) : p->width);
	while (!p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)p->len || p->temp_s[0] == 48 ? 0 : p->sharp_on) -
		(ft_abs(p->precision) > (int)p->len ?
		(ft_abs(p->precision) - (int)p->len) : 0) -
		(int)p->len) > 0)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	if (p->sharp_on && ((p->prec_found && !p->dotnull) ||
		(!p->prec_found && p->temp_s[0] != 48)))
		p->buf[p->ret++] = '0';
	while ((p->precision - (int)p->len -
		p->sharp_on - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	funct_for_o3(p);
}

void			funct_for_o(t_p *p)
{
	if (p->temp_s[0] == 48)
		p->kostyl1 = 1;
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->temp_s[0] == 48 && p->precision == 1)
		p->dotnull = 1;
	if (p->width >= ft_abs(p->precision))
		funct_for_o2(p);
	else
		funct_for_o4(p);
	ft_strdel(&p->temp_s);
}
