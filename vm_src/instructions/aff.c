/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 15:06:11 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 15:06:12 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		aff(t_lst *carry, t_vm *vm)
{
	int n;

	if (vm->a_flag == 1)
	{
		n = carry->registry[vm->map[carry->pc].val - 1];
		write(1, "Aff: ", 5);
		write(1, &n, 1);
		write(1, "\n", 1);
	}
	iterate(&carry->pc, 1);
	return (0);
}
