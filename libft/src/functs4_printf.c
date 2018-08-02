/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:06:55 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:06:58 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		funct_for_ws3(t_p *p)
{
	while (p->width && !p->minus_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	while (*p->temp_ws)
	{
		if (p->stop)
			break ;
		p->temp_wc = (unsigned int)(*p->temp_ws++);
		funct_for_wc(p);
	}
	while (p->width && p->minus_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	while (p->precision < 0 && p->prec_found)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_ws2(t_p *p)
{
	p->temp_s = ft_strdup("(null)");
	if (p->precision >= 0 && 6 > (size_t)p->precision)
		p->temp_s[p->precision] = 0;
	check_the_buf(p, (p->len = ft_strlen(p->temp_s)) > (size_t)p->width ?
		p->len : p->width);
	while ((p->width - (int)p->len) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, p->len);
	p->ret += p->len;
	while ((p->width - (int)p->len) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	ft_strdel(&p->temp_s);
}

void			funct_for_ws(t_p *p)
{
	p->temp_ws = va_arg(p->ap, wchar_t*);
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (!p->temp_ws)
	{
		funct_for_ws2(p);
		return ;
	}
	if (p->sharp_undef || p->minus_undef)
		p->temp_ws = (wchar_t*)"\0";
	p->j = -1;
	while (p->temp_ws[++p->j])
	{
		p->temp_wc = p->temp_ws[p->j];
		p->wd = check_the_width(p);
		if (p->precision < 0 || (p->precision - p->wd >= 0))
		{
			p->awd += p->wd;
			p->precision -= p->wd;
		}
		else
			break ;
	}
	(p->width - p->awd) < 0 ? (p->width = 0) : (p->width -= p->awd);
	funct_for_ws3(p);
}
