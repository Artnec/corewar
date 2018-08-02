/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:20:48 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/31 20:20:50 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add(t_lst *carry, t_vm *vm)
{
	int r1;
	int r2;

	r1 = carry->pc;
	r2 = iterate(&carry->pc, 1);
	iterate(&carry->pc, 1);
	carry->registry[vm->map[carry->pc].val - 1] =
	carry->registry[vm->map[r1].val - 1] + carry->registry[vm->map[r2].val - 1];
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
