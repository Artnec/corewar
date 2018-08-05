/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 20:37:33 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/27 20:37:34 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		and(t_lst *carry, t_vm *vm)
{
	int j;
	int n;

	j = carry->codage >> 2;
	n = (int)get_rdi_val(carry, j >> 2, 4, vm) &
		(int)get_rdi_val(carry, j & 3, 4, vm);
	carry->registry[vm->map[carry->pc].val - 1] = n;
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
