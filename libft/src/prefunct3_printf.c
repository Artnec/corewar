/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefunct3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:06:27 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:06:29 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		prefunct_for_big_x2(t_p *p)
{
	if (p->l_on > 1)
	{
		p->temp_ull = va_arg(p->ap, unsigned long long);
		p->temp_s = ft_uixtoa_base(p->temp_ull, 16);
	}
	else if (p->h_on == 1)
	{
		p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
		p->temp_s = ft_uixtoa_base(p->temp_ui, 16);
	}
	else if (p->h_on > 1)
	{
		p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
		p->temp_s = ft_uixtoa_base(p->temp_ui, 16);
	}
	else
	{
		p->temp_ui = va_arg(p->ap, unsigned int);
		p->temp_s = ft_uixtoa_base(p->temp_ui, 16);
	}
	funct_for_x(p);
}

void			prefunct_for_big_x(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_uixtoa_base(p->temp_st, 16);
		funct_for_x(p);
	}
	else if (p->j_on)
	{
		p->temp_um = va_arg(p->ap, uintmax_t);
		p->temp_s = ft_uixtoa_base(p->temp_um, 16);
		funct_for_x(p);
	}
	else if (p->l_on == 1)
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_uixtoa_base(p->temp_ul, 16);
		funct_for_x(p);
	}
	else
		prefunct_for_big_x2(p);
}

static void		prefunct_for_x2(t_p *p)
{
	if (p->l_on > 1)
	{
		p->temp_ull = va_arg(p->ap, unsigned long long);
		p->temp_s = ft_ulxtoa_base(p->temp_ull, 16);
	}
	else if (p->h_on == 1)
	{
		p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 16);
	}
	else if (p->h_on > 1)
	{
		p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 16);
	}
	else
	{
		p->temp_ui = va_arg(p->ap, unsigned int);
		p->temp_s = ft_ulxtoa_base(p->temp_ui, 16);
	}
	funct_for_x(p);
}

void			prefunct_for_x(t_p *p)
{
	if (p->z_on)
	{
		p->temp_st = va_arg(p->ap, size_t);
		p->temp_s = ft_ulxtoa_base(p->temp_st, 16);
		funct_for_x(p);
	}
	else if (p->j_on)
	{
		p->temp_um = va_arg(p->ap, uintmax_t);
		p->temp_s = ft_ulxtoa_base(p->temp_um, 16);
		funct_for_x(p);
	}
	else if (p->l_on == 1)
	{
		p->temp_ul = va_arg(p->ap, unsigned long);
		p->temp_s = ft_ulxtoa_base(p->temp_ul, 16);
		funct_for_x(p);
	}
	else
		prefunct_for_x2(p);
}
