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

int		lld(t_carry *carry, t_vm *vm)
{
	int n;

	iterate(&carry->pc, 1);
	if (vm->map[carry->pc].val == 0xd0)
	{
		n = (carry->pc + get_usrt(vm->map, carry->pc + 1)) % MEM_SIZE;
		carry->registry[vm->map[carry->pc + 3].val - 1] = get_uint(vm->map, n);
		carry->carry = carry->registry[vm->map[carry->pc + 3].val - 1] == 0 ? 1 : 0;
		iterate(&carry->pc, 4);
	}
	else if (vm->map[carry->pc].val == 0x90)
	{
		carry->registry[vm->map[carry->pc + 5].val - 1] = get_uint(vm->map, carry->pc + 1);
		carry->carry = carry->registry[vm->map[carry->pc + 5].val - 1] == 0 ? 1 : 0;
		iterate(&carry->pc, 6);
	}
	return (0);
}

