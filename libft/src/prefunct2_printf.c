/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefunct2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:06:20 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:06:22 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		prefunct_for_u2(t_p *p)
{
	if (p->l_on > 1)
	{
		p->temp_ull = va_arg(p->ap, unsigned long long);
		p->temp_s = ft_ulxtoa_base(p->temp_ull, 10);
	}
	else if (p->h_on == 1)
	{
		p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 10);
	}
	else if (p->h_on > 1)
	{
		p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 10);
	}
	else
	{
		p->temp_ui = va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 10);
	}
	funct_for_u(p);
}

void			prefunct_for_u(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_ulxtoa_base(p->temp_st, 10);
		funct_for_u(p);
	}
	else if (p->j_on)
	{
		p->temp_um = va_arg(p->ap, uintmax_t);
		p->temp_s = ft_ulxtoa_base(p->temp_um, 10);
		funct_for_u(p);
	}
	else if (p->l_on == 1)
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_ulxtoa_base(p->temp_ul, 10);
		funct_for_u(p);
	}
	else
		prefunct_for_u2(p);
}

void			prefunct_for_big_o(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_ulxtoa_base(p->temp_st, 8);
	}
	else if (p->j_on)
	{
		p->temp_um = va_arg(p->ap, uintmax_t);
		p->temp_s = ft_ulxtoa_base(p->temp_um, 8);
	}
	else if (p->l_on > 1)
	{
		p->temp_ull = va_arg(p->ap, unsigned long long);
		p->temp_s = ft_ulxtoa_base(p->temp_ull, 8);
	}
	else
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_ulxtoa_base(p->temp_ul, 8);
	}
	funct_for_o(p);
}

static void		prefunct_for_o2(t_p *p)
{
	if (p->l_on > 1)
	{
		p->temp_ull = va_arg(p->ap, unsigned long long);
		p->temp_s = ft_ulxtoa_base(p->temp_ull, 8);
	}
	else if (p->h_on == 1)
	{
		p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 8);
	}
	else if (p->h_on > 1)
	{
		p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 8);
	}
	else
	{
		p->temp_ui = va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 8);
	}
	funct_for_o(p);
}

void			prefunct_for_o(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_ulxtoa_base(p->temp_st, 8);
		funct_for_o(p);
	}
	else if (p->j_on)
	{
		p->temp_um = va_arg(p->ap, uintmax_t);
		p->temp_s = ft_ulxtoa_base(p->temp_um, 8);
		funct_for_o(p);
	}
	else if (p->l_on == 1)
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_ulxtoa_base(p->temp_ul, 8);
		funct_for_o(p);
	}
	else
		prefunct_for_o2(p);
}
