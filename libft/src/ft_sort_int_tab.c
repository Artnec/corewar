/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:53:21 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 14:53:22 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i;
	int				swap;
	unsigned int	l;

	i = 0;
	if (!tab || !size)
		return ;
	while (i < size)
	{
		l = 0;
		while (l + i < size)
		{
			if (tab[i] > tab[l + i])
			{
				swap = tab[l + i];
				tab[l + i] = tab[i];
				tab[i] = swap;
			}
			l++;
			if (l + i == size)
				i++;
		}
	}
}
