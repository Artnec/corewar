/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 15:28:17 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 15:28:18 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lldi(t_list *carry, t_vm *vm)
{
	int j;
	int n;

	carry->p = carry->pc;
	iterate(&carry->p, 1);
	j = vm->map[carry->p].val >> 4;
	iterate(&carry->p, 1);
	n = ((int)get_rdi_val(carry, j >> 2, 2, vm) + (int)get_rdi_val(carry, j & 3, 2, vm));
	if (vm->map[carry->pc].val < 1 || vm->map[carry->pc].val > REG_NUMBER)
	{
		iterate(&carry->pc, 1);
		return (0);
	}
	iterate(&carry->pc, n);
	n = get_uint(vm->map, carry->pc);
	carry->registry[vm->map[carry->p].val - 1] = n;
	carry->carry = (n == 0 ? 1 : 0);
	carry->pc = iterate(&carry->p, 1);
	return (0);
}
