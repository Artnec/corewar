/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:19:24 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/26 16:19:25 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



int		lld(t_list *carry, t_vm *vm)
{
	int n;
	int t;

	// printf("lld\n");
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	if (vm->map[carry->p].val == 0xd0)
	{
		iterate(&carry->p, 1);
		n = (carry->pc + get_usrt(vm->map, carry->p)) % MEM_SIZE;
		iterate(&carry->p, 2);
		if (vm->map[carry->p].val < 1 || vm->map[carry->p].val > REG_NUMBER)
		{
			carry->pc = iterate(&carry->p, 1);
			return (0);
		}
		t = get_uint(vm->map, n);
		t = t > 0x7fffffff ? (t >> 16) | 0xffff0000 : t >> 16;
		carry->registry[vm->map[carry->p].val - 1] = t;
		carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
		carry->pc = iterate(&carry->p, 1);
	}
	else if (vm->map[carry->p].val == 0x90)
	{
		iterate(&carry->p, 1);
		n = get_uint(vm->map, carry->p);
		iterate(&carry->p, 4);
		if (vm->map[carry->p].val < 1 || vm->map[carry->p].val > REG_NUMBER)
		{
			carry->pc = iterate(&carry->p, 1);
			return (0);
		}
		carry->registry[vm->map[carry->p].val - 1] = n;
		carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
		carry->pc = iterate(&carry->p, 1);
	}
	return (0);
}
