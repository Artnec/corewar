/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_prime_sum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:23:02 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:23:03 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Function returns the sum of all prime numbers of "nb"
*/

#include "../include/libft.h"

int		ft_add_prime_sum(int nb)
{
	int count;
	int sum;

	count = 2;
	sum = 0;
	while (count <= nb)
	{
		if (ft_isprime(count) == 1)
			sum = sum + count;
		count++;
	}
	return (sum);
}
