/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 11:13:10 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 11:13:12 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st(t_list *carry, t_vm *vm)
{
	int j;
	int r;
	int n;

	carry->p = carry->pc;
	iterate(&carry->p, 1);
	j = (vm->map[carry->p].val & 0x30) >> 4;
	r = iterate(&carry->p, 1);
	if (vm->map[r].val < 1 || vm->map[r].val > REG_NUMBER)
	{
		carry->pc = iterate(&carry->p, j == REG_CODE ? 2 : 3);
		return (0);
	}
	iterate(&carry->p, 1);
	if (j == REG_CODE) // check reg
		carry->registry[vm->map[carry->p].val - 1] = carry->registry[vm->map[r].val - 1];
	else
	{
		n = carry->pc + (short)get_usrt(vm->map, carry->p) % IDX_MOD;
		uint_to_map(carry->registry[vm->map[r].val - 1], carry->id, vm->map, n);
	}
	carry->pc = iterate(&carry->p, j == REG_CODE ? 1 : 2);
	return (0);
}
