/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 15:28:05 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 15:28:06 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ldi(t_list *carry, t_vm *vm)
{
	int j;
	int n;

	carry->p = carry->pc;
	iterate(&carry->p, 1);
	j = vm->map[carry->p].val >> 4;
	iterate(&carry->p, 1);
	n = ((int)get_rdi_val(carry, j >> 2, 2, vm) + (int)get_rdi_val(carry, j & 3, 2, vm)) % IDX_MOD;
	if (vm->map[carry->pc].val < 1 || vm->map[carry->pc].val > REG_NUMBER)
	{
		iterate(&carry->pc, 1);
		return (0);
	}
	iterate(&carry->pc, n);
	n = get_uint(vm->map, carry->pc);
	carry->registry[vm->map[carry->p].val - 1] = n;
	// printf("w %d %d\n", carry->registry[vm->map[carry->p].val - 1], vm->map[carry->p].val);
	carry->pc = iterate(&carry->p, 1);
	return (0);
}

