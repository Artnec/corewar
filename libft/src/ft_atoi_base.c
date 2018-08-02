/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:41:14 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 14:41:15 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		transform(char s)
{
	if (s >= 48 && s <= 57)
		return (s - 48);
	if (s >= 65 && s <= 70)
		return (s - 65 + 10);
	if (s >= 97 && s <= 102)
		return (s - 97 + 10);
	return (-1);
}

int				ft_atoi_base(const char *str, int str_base)
{
	int indicator;
	int number;
	int res;

	res = 0;
	indicator = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			indicator = 1;
		str++;
	}
	number = transform(*str);
	while (number >= 0 && *str)
	{
		res = res * str_base + number;
		str++;
		number = transform(*str);
	}
	if (indicator == 1)
		return (-res);
	return (res);
}
