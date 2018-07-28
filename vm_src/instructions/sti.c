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

int		sti(t_carry *carry, t_vm *vm)
{
	int j;
	int r;
	int n;

	printf("sti\n");
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	j = (vm->map[carry->p].val & 0x3c) >> 2;
	r = iterate(&carry->p, 1);
	iterate(&carry->p, 1);
	n = carry->pc + ((int)(get_rdi_val(carry, j >> 2, 2, vm) + get_rdi_val(carry, j & 3, 2, vm)) % IDX_MOD);
	printf("n: %d\n", n);
	uint_to_map(carry->registry[vm->map[r].val - 1], carry->id, vm->map, n);
	carry->pc = carry->p;
	return (0);
}

// #define ITE(x, y)	(x + y < 0 ? MEM_SIZE + (x + y) % MEM_SIZE : (x + y) % MEM_SIZE)
