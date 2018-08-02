/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:06:46 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:06:47 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		cut(t_p *p)
{
	char	*temp;
	int		i;

	if (!(temp = (char*)ft_memalloc(sizeof(char) * (p->precision + 1))))
		p->error = 1;
	i = -1;
	while (++i < p->precision)
		temp[i] = p->temp_s[i];
	p->temp_s = temp;
	p->cut = 1;
}

static void		funct_for_s2(t_p *p)
{
	if (p->sharp_undef || p->minus_undef)
		p->temp_s = "";
	if (p->precision >= 0 && ft_strlen(p->temp_s) > (size_t)p->precision)
		cut(p);
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
	while (p->precision < 0 && p->prec_found)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
	if (p->cut)
		ft_strdel(&p->temp_s);
}

static void		funct_for_s1(t_p *p)
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

void			funct_for_s(t_p *p)
{
	p->temp_s = va_arg(p->ap, char*);
	if (p->prec_found && p->precision < 0)
	{
		p->width = ft_abs(p->precision);
		p->precision = 0;
	}
	if (!p->temp_s)
		funct_for_s1(p);
	else
		funct_for_s2(p);
}
