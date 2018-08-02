/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:25:23 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/04 19:25:24 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		check_the_flags3(t_p *p)
{
	if (p->fmt[p->i] == 'C' || (p->fmt[p->i] == 'c' && p->l_on))
		prefunct_for_wc(p);
	else if (p->fmt[p->i] == 'O')
		prefunct_for_big_o(p);
	else if (p->fmt[p->i] == 'o')
		prefunct_for_o(p);
	else if (p->fmt[p->i] == 'X')
		prefunct_for_big_x(p);
	else if (p->fmt[p->i] == 'x')
		prefunct_for_x(p);
	else
		p->i--;
}

static void		check_the_flags2(t_p *p)
{
	if (p->fmt[p->i] == '%')
		funct_for_percent(p);
	else if (p->fmt[p->i] == 'c' && !p->l_on)
		funct_for_c(p);
	else if (p->fmt[p->i] == 's' && p->l_on != 1)
		funct_for_s(p);
	else if (p->fmt[p->i] == 'D')
		prefunct_for_big_d(p);
	else if (p->fmt[p->i] == 'd' || p->fmt[p->i] == 'i')
		prefunct_for_d(p);
	else if (p->fmt[p->i] == 'U')
		prefunct_for_big_u(p);
	else if (p->fmt[p->i] == 'u')
		prefunct_for_u(p);
	else if (p->fmt[p->i] == 'p')
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_ulxtoa_base(p->temp_ul, 16);
		funct_for_p(p);
	}
	else if (p->fmt[p->i] == 'S' || (p->fmt[p->i] == 's' && p->l_on))
		funct_for_ws(p);
	else
		check_the_flags3(p);
}

static void		without_spec2(t_p *p)
{
	while ((p->width - 1) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	p->buf[p->ret++] = p->without_spec[0];
	while ((p->width - 1) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	ft_memcpy(p->buf + p->ret, p->without_spec + 1, p->len - 1);
	p->ret += p->len - 1;
}

static void		without_spec(t_p *p)
{
	if (p->precision < 0 && p->prec_found)
		p->width = ft_abs(p->precision);
	while (p->fmt[p->i] != '%' && p->fmt[p->i])
	{
		p->i++;
		p->j++;
	}
	if (!(p->without_spec = (char*)ft_memalloc(sizeof(char) * (p->j + 1))))
		p->error = 1;
	ft_memcpy(p->without_spec, p->fmt + (p->i -= p->j), (size_t)p->j);
	check_the_buf(p, (p->len = ft_strlen(p->without_spec)) + p->width -
		(p->width > 0 ? 1 : 0));
	without_spec2(p);
	ft_strdel(&p->without_spec);
	p->i += p->j - 1;
}

void			check_the_flags(t_p *p)
{
	while (p->fmt[++p->i] && !(A(p->fmt[p->i])) && !(A1(p->fmt[p->i])) &&
		!(A2(p->fmt[p->i])))
	{
		if (!(p->fmt[p->i] >= 48 && p->fmt[p->i] <= 57) &&
			!(B(p->fmt[p->i])) && !(B1(p->fmt[p->i])))
		{
			p->found = 0;
			break ;
		}
		if ((size_t)p->j == p->spec_size)
			more_spec(p);
		p->spec[p->j++] = p->fmt[p->i];
	}
	p->j = -1;
	while (p->spec[++p->j])
		look_for_specificators(p);
	p->j = 0;
	if (p->found)
	{
		if (p->precision >= 0 && !(C(p->fmt[p->i])))
			p->zero_on = 0;
		check_the_flags2(p);
	}
	else
		without_spec(p);
}
