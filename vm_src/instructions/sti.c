/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 21:14:01 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/24 21:14:03 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	get_rdi_val(t_carry *carry, int t_rdi, int d, t_vm *vm)
{
	// printf("j: %d\n", t_rdi);
	if (t_rdi == REG_CODE)
	{
		// printf("T_REG\n");
		return (carry->registry[vm->map[carry->pc++].val]);
	}
	if (t_rdi == DIR_CODE)
	{
		// printf("T_DIR\n");
		carry->pc += d;
		if (d == 2)
			return(get_usrt(vm->map + carry->pc - d));
		return (get_uint(vm->map + carry->pc - d));
	}
	if (t_rdi == IND_CODE)
	{
		// printf("T_IND\n");
		carry->pc += 2;
		return (get_uint(vm->map + get_usrt(vm->map + carry->pc - 2) % IDX_MOD));
	}
	// error ???
	return (0);
}

int		sti(t_carry *carry, t_vm *vm)
{
	// printf("sti\n");
	// printf("map %02x\n", vm->map[carry->pc + 1].val);
	int j = (vm->map[++carry->pc].val & 0x3c) >> 2;
	int r = ++carry->pc;
	carry->pc += 1;
	// printf("%d %d\n", vm->map[carry->pc - 1].val, carry->registry[vm->map[carry->pc - 1].val]);
	int n = carry->pc + (get_rdi_val(carry, j >> 2, 2, vm) + get_rdi_val(carry, j & 3, 2, vm) - 3) % IDX_MOD;
	uint_to_map(carry->registry[vm->map[r].val], carry->id, vm->map + n);
	return (0);
}
