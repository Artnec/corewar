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

int		sti(t_lst *carry, t_vm *vm)
{
	int j;
	int r;
	int n;

	j = carry->codage & 0xf;
	r = carry->pc;
	iterate(&carry->pc, 1);
	n = ((int)(get_rdi_val(carry, j >> 2, 2, vm) +
		get_rdi_val(carry, j & 3, 2, vm)) % IDX_MOD);
	j = carry->op;
	iterate(&j, n);
	uint_to_map(carry->registry[vm->map[r].val - 1], carry->id, vm, j);
	return (0);
}
