/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs_for_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:06:17 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/06 18:06:18 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void			funct_for_percent(t_p *p)
{
	if (p->precision < 0 && p->prec_found)
		p->width = ft_abs(p->precision);
	check_the_buf(p, (1 > p->width ? 1 : p->width));
	while ((p->width - 1) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	p->buf[p->ret++] = '%';
	while ((p->width - 1) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
}

void			funct_for_c(t_p *p)
{
	p->temp_c = va_arg(p->ap, int);
	if (p->precision < 0 && p->prec_found)
		p->width = ft_abs(p->precision);
	check_the_buf(p, (1 > p->width ? 1 : p->width));
	while ((p->width - 1) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	p->buf[p->ret++] = p->temp_c;
	while ((p->width - 1) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
}

static void		funct_for_p2(t_p *p)
{
	while ((p->width - (p->precision > (int)p->len ?
		(p->precision - (int)p->len) : 0) -
		(int)p->len - 2) > 0 && !p->minus_on && p->zero_on)
	{
		p->buf[p->ret++] = 48;
		p->width--;
	}
	while ((p->precision - (int)p->len - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while ((p->width - (p->precision > (int)p->len ?
		(p->precision - (int)p->len) : 0) - (int)p->len - 2) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		(int)p->len - 2) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
	ft_strdel(&p->temp_s);
}

void			funct_for_p(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->precision < 0 && p->prec_found)
	{
		p->width = ft_abs(p->precision);
		p->precision = 0;
	}
	if (p->width >= ft_abs(p->precision))
		check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + 2 >
			(size_t)p->width ? (p->len + 2) : p->width));
	else
		check_the_buf(p, ((p->len = ft_strlen(p->temp_s)) + 2 >
			(size_t)(ft_abs(p->precision) + 2) ?
			(p->len + 2) : (ft_abs(p->precision) + 2)));
	while ((p->width - (p->precision > (int)p->len ? (p->precision -
		(int)p->len) : 0) - (int)p->len - 2) > 0 && !p->minus_on && !p->zero_on)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
	p->buf[p->ret++] = '0';
	p->buf[p->ret++] = 'x';
	funct_for_p2(p);
}

void			funct_for_wc(t_p *p)
{
	p->wd = check_the_width(p);
	if (p->wd <= p->awd)
		check_the_buf(p, p->wd);
	if (p->wd == 1 && p->awd >= 1)
		p->buf[p->ret++] = p->temp_wc;
	else if (p->wd == 2 && p->awd >= 2)
	{
		p->buf[p->ret++] = (p->temp_wc >> 6) | 192;
		p->buf[p->ret++] = (p->temp_wc | 128) & 191;
	}
	else if (p->wd == 3 && p->awd >= 3)
	{
		p->buf[p->ret++] = (p->temp_wc >> 12) | 224;
		p->buf[p->ret++] = ((p->temp_wc >> 6) | 128) & 191;
		p->buf[p->ret++] = (p->temp_wc | 128) & 191;
	}
	else if (p->wd == 4 && p->awd >= 4)
	{
		p->buf[p->ret++] = (p->temp_wc >> 18) | 240;
		p->buf[p->ret++] = ((p->temp_wc >> 12) | 128) & 191;
		p->buf[p->ret++] = ((p->temp_wc >> 6) | 128) & 191;
		p->buf[p->ret++] = (p->temp_wc | 128) & 191;
	}
	(p->wd >= 1 && p->awd >= p->wd) ? (p->awd -= p->wd) : (p->stop = 1);
}
