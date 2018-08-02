/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:16:57 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:16:58 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Function returns 1 if a number is prime and 0 if not.
*/

int		ft_isprime(int count)
{
	int div;

	div = 2;
	while (div < count)
	{
		if (count % div == 0)
			return (0);
		div++;
	}
	return (1);
}
