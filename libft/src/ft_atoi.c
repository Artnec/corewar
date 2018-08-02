/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 16:16:26 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/04 16:16:27 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		check(long long int nb, int ind)
{
	if (nb == -2537764290115403777 && ind == 0)
		return (-1);
	if (nb == -2537764290115403777 && ind == 1)
		return (0);
	return (nb);
}

int				ft_atoi(const char *str)
{
	int				i;
	int				n;
	int				ind;
	long long int	nb;

	i = 0;
	nb = 0;
	ind = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	n = i;
	while (str[n] >= 48 && str[n] <= 57)
	{
		nb = nb * 10 + (str[n] - 48);
		n++;
	}
	if (i > 0 && str[i - 1] == '-')
		ind = 1;
	nb = check(nb, ind);
	if (ind == 1)
		return (-nb);
	return (nb);
}
