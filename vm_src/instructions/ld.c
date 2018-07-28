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

int		ld(t_carry *carry, t_vm *vm)
{
	int n;

	printf("ld\n");
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	if (vm->map[carry->p].val == 0xd0)
	{
		iterate(&carry->p, 1);
		n = (carry->pc + get_usrt(vm->map, carry->p) % IDX_MOD) % MEM_SIZE;
		// printf("%d %d\n", get_usrt(vm->map, carry->p), carry->pc);
		iterate(&carry->p, 2);
		carry->registry[vm->map[carry->p].val - 1] = get_uint(vm->map, n);
		carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
		carry->pc = iterate(&carry->p, 1);
	}
	else if (vm->map[carry->p].val == 0x90)
	{
		iterate(&carry->p, 1);
		n = get_uint(vm->map, carry->p);
		iterate(&carry->p, 4);
		carry->registry[vm->map[carry->p].val - 1] = n;
		carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
		carry->pc = iterate(&carry->p, 1);
	}
	return (0);
}
