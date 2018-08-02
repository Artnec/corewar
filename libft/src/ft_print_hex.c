/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:39:16 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:39:18 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_print_hex(unsigned int nbr)
{
	if (nbr >= 16)
		ft_print_hex(nbr / 16);
	if ((nbr % 16) < 10)
		ft_putchar((nbr % 16) + 48);
	else
		ft_putchar((nbr % 16) - 10 + 97);
}
