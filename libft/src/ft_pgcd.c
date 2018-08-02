/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pgcd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:37:19 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:37:20 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Returns the highest common denominator of a and b.
*/

int		ft_pgcd(int a, int b)
{
	int j;
	int div;

	j = 1;
	div = 0;
	while (j <= a && j <= b)
	{
		if ((a % j) == 0 && (b % j) == 0)
			div = j;
		j++;
	}
	return (div);
}
