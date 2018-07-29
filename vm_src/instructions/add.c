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

int		add(t_list *carry, t_vm *vm)
{
	int r1;
	int r2;

	carry->p = carry->pc;
	r1 = iterate(&carry->p, 2);
	r2 = iterate(&carry->p, 1);
	iterate(&carry->p, 1);
	if (RC(vm->map[r1].val) || RC(vm->map[r2].val) || RC(vm->map[carry->p].val))
	{
		carry->pc = iterate(&carry->p, 1);
		return (0);
	}
	carry->registry[vm->map[carry->p].val - 1] =
	carry->registry[vm->map[r1].val - 1] + carry->registry[vm->map[r2].val - 1];
	carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->p, 1);
	return (0);
}
