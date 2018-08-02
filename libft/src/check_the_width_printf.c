/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:07:53 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/21 16:07:56 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		check_the_width(t_p *p)
{
	if (p->temp_wc < 0 || p->temp_wc > 1114111 || (p->temp_wc > 55295 &&
		p->temp_wc < 57344))
		p->error = 1;
	else if (MB_CUR_MAX == 1 && p->temp_wc > 255)
		p->error = 1;
	else if (MB_CUR_MAX == 1 && p->temp_wc < 256)
		return (1);
	else if (MB_CUR_MAX == 4)
	{
		p->sl_on = 1;
		if (p->temp_wc <= 127)
			return (1);
		else if (p->temp_wc <= 2047)
			return (2);
		else if (p->temp_wc <= 65535)
			return (3);
		else if (p->temp_wc <= 1114111)
			return (4);
	}
	return (0);
}
