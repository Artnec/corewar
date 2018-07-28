/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:42 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/31 21:58:44 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sub(t_carry *carry, t_vm *vm)
{
	int r1;
	int r2;

	carry->p = carry->pc;
	r1 = iterate(&carry->p, 2);
	r2 = iterate(&carry->p, 1);
	iterate(&carry->p, 1);
	carry->registry[vm->map[carry->p].val - 1] =
	carry->registry[vm->map[r1].val - 1] - carry->registry[vm->map[r2].val - 1];
	carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->p, 1);
	return (0);
}


// int		sub(t_carry *carry, t_vm *vm)
// {
// 	int n;

// 	iterate(&carry->pc, 1);
// 	if (vm->map[carry->pc].val != 0x54)
// 		return (0);
// 	n = iterate(&carry->pc, 1);
// 	carry->registry[vm->map[n + 2].val - 1] =
// 	carry->registry[vm->map[n].val - 1] - carry->registry[vm->map[n + 1].val - 1];
// 	carry->carry = carry->registry[vm->map[n + 2].val - 1] == 0 ? 1 : 0;
// 	iterate(&carry->pc, 3);
// 	return (0);
// }
