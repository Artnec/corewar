/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:19:24 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/26 16:19:25 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lld(t_lst *carry, t_vm *vm)
{
	int n;
	int t;

	if ((carry->codage & 0x3c) == 0x34)
	{
		n = carry->op;
		iterate(&n, (short)get_short(vm->map, carry->pc) % MEM_SIZE);
		t = get_uint(vm->map, n);
		t = t > 0x7fffffff ? (t >> 16) | 0xffff0000 : t >> 16;
		iterate(&carry->pc, 2);
		carry->registry[vm->map[carry->pc].val - 1] = t;
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
