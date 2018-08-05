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

int		ldi(t_lst *carry, t_vm *vm)
{
	int j;
	int n;

	j = carry->codage >> 2;
	j = ((int)get_rdi_val(carry, j >> 2, 2, vm) +
		(int)get_rdi_val(carry, j & 3, 2, vm)) % IDX_MOD;
	n = carry->op;
	iterate(&n, j);
	n = get_uint(vm->map, n);
	carry->registry[vm->map[carry->pc].val - 1] = n;
	iterate(&carry->pc, 1);
	return (0);
}
