/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 21:14:14 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/24 21:14:15 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ld(t_lst *carry, t_vm *vm)
{
	int n;

	if ((carry->codage & 0x3c) == 0x34)
	{
		n = carry->op;
		iterate(&n, ((short)get_short(vm->map, carry->pc) % IDX_MOD) %
			MEM_SIZE);
		iterate(&carry->pc, 2);
		carry->registry[vm->map[carry->pc].val - 1] = get_uint(vm->map, n);
	}
	else if ((carry->codage & 0x3c) == 0x24)
	{
		n = get_uint(vm->map, carry->pc);
		iterate(&carry->pc, 4);
		carry->registry[vm->map[carry->pc].val - 1] = n;
	}
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
