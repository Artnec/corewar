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

int		lldi(t_lst *carry, t_vm *vm)
{
	int j;
	int n;

	j = carry->codage >> 2;
	n = ((int)get_rdi_val(carry, j >> 2, 2, vm) +
		(int)get_rdi_val(carry, j & 3, 2, vm));
	j = carry->op;
	iterate(&j, n);
	n = get_uint(vm->map, j);
	carry->registry[vm->map[carry->pc].val - 1] = n;
	carry->carry = (n == 0 ? 1 : 0);
	iterate(&carry->pc, 1);
	return (0);
}
