/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_specificators.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:30:02 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/02 16:30:03 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int		precision3(t_p *p)
{
	if (p->spec[p->j] == 'l' && (B(p->spec[p->j + 1]) || B1(p->spec[p->j + 1])
		|| !p->spec[p->j + 1]))
		p->l_on++;
	else if (p->spec[p->j] == 'h' && (B(p->spec[p->j + 1]) ||
		B1(p->spec[p->j + 1]) || !p->spec[p->j + 1]))
		p->h_on++;
	else if (p->spec[p->j] > 48 && p->spec[p->j] <= 57)
	{
		p->prec_found = 1;
		p->precision = ft_atoi(p->spec + p->j);
		while (p->spec[p->j] >= 48 && p->spec[p->j] <= 57)
			p->j++;
		p->j--;
		return (0);
	}
	return (1);
}

static int		precision2(t_p *p)
{
	while (B(p->spec[p->j]) || B1(p->spec[p->j]) || D(p->spec[p->j]))
	{
		if (p->spec[p->j] == ' ')
		{
			p->j++;
			look_for_specificators(p);
			break ;
		}
		else if (p->spec[p->j] == '#')
		{
			look_for_specificators(p);
			return (0);
		}
		else if (p->spec[p->j] == '-')
			look_for_specificators(p);
		else if (p->spec[p->j] == '+')
		{
			look_for_specificators(p);
			break ;
		}
		else if (!precision3(p))
			return (0);
		p->j++;
	}
	return (1);
}

static int		precision(t_p *p)
{
	p->j++;
	if (p->prec_found && p->precision < 0)
		p->width = ft_abs(p->precision);
	p->precision = 0;
	return (precision2(p));
}

static void		next(t_p *p)
{
	if (p->spec[p->j] == '#')
	{
		p->sharp_on = 1;
		if (p->spec[p->j - 1] == '.')
			p->sharp_undef = 1;
	}
	else if (p->spec[p->j] == 'l')
		p->l_on++;
	else if (p->spec[p->j] == 'h')
		p->h_on++;
	else if (p->spec[p->j] == 'j')
		p->j_on = 1;
	else if (p->spec[p->j] == 'z')
		p->z_on = 1;
	else if (p->spec[p->j] > 48 && p->spec[p->j] <= 57)
	{
		p->width = ft_abs(ft_atoi(p->spec + p->j));
		while (p->spec[p->j] >= 48 && p->spec[p->j] <= 57)
			p->j++;
		p->j--;
	}
}

void			look_for_specificators(t_p *p)
{
	if (p->spec[p->j] == 32 && !p->plus_on)
		p->spaces = 1;
	else if (p->spec[p->j] == 48 && !p->minus_on && p->precision < 0)
		p->zero_on = 1;
	else if (p->spec[p->j] == '-')
	{
		p->minus_on = 1;
		p->zero_on = 0;
		if (p->spec[p->j - 1] == '.')
			p->minus_undef = 1;
	}
	else if (p->spec[p->j] == '.')
	{
		if (!precision(p))
			return ;
	}
	else if (p->spec[p->j] == '+')
	{
		p->plus_on = 1;
		p->spaces = 0;
	}
	else
		next(p);
}
