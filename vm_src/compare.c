/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:38:27 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/25 14:38:28 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		str_num_compare(unsigned char *s, unsigned int num)
{
	return ((unsigned int)(s[3] | s[2] << 8 | s[1] << 16 | s[0] << 24) == num);
}

// int		mem_compare(void *one, void *two, int n)
// {
// 	int				i;
// 	unsigned char	*a;
// 	unsigned char	*b;

// 	a = one;
// 	b = two;
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (a[i] != b[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
