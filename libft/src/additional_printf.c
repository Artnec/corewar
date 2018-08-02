/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:22:53 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:22:54 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	minus_del(t_p *p)
{
	int		i;

	if ((p->width && p->zero_on) || ((p->precision >= p->width) ||
		(p->precision < 0)))
		p->buf[p->ret++] = '-';
	p->plus_on = 0;
	i = 0;
	while (p->temp_s[++i])
		p->temp_s[i - 1] = p->temp_s[i];
	p->temp_s[--i] = 0;
	p->width--;
	p->minus_del = 1;
}

void	more_spec(t_p *p)
{
	char	*temp;

	temp = p->spec;
	if (!(p->spec = (char*)ft_memalloc(sizeof(char) *
		((p->spec_size += 10) + 1))))
		p->error = 1;
	ft_memcpy(p->spec, temp, p->j);
	ft_strdel(&temp);
}
