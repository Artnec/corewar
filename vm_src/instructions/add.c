/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:20:48 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/31 20:20:50 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add(t_carry *carry, t_vm *vm)
{
	int n;

	iterate(&carry->pc, 1);
	if (vm->map[carry->pc].val != 0x54)
		return (0);
	n = iterate(&carry->pc, 1);
	carry->registry[vm->map[n + 2].val - 1] =
	carry->registry[vm->map[n].val - 1] + carry->registry[vm->map[n + 1].val - 1];
	carry->carry = carry->registry[vm->map[n + 2].val - 1] == 0 ? 1 : 0;
	iterate(&carry->pc, 3);
	return (0);
}
