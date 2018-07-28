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



int		lld(t_carry *carry, t_vm *vm)
{
	int n;
	int t;

	printf("lld\n");
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	if (vm->map[carry->p].val == 0xd0)
	{
		// printf("a\n");
		iterate(&carry->p, 1);
		n = (carry->pc + get_usrt(vm->map, carry->p)) % MEM_SIZE;
		// printf("%d %d\n", get_usrt(vm->map, carry->p), carry->pc);
		iterate(&carry->p, 2);
		t = get_uint(vm->map, n);
		// printf("%x\n", t & 0x0000ffff);
		t = t > 0x7fffffff ? (t >> 16) | 0xffff0000 : t >> 16;
		carry->registry[vm->map[carry->p].val - 1] = t;
		// carry->registry[vm->map[carry->p].val - 1] = get_usrt(vm->map, n) | 0xffff0000;
		carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
		carry->pc = iterate(&carry->p, 1);
		// printf("aa\n");
	}
	else if (vm->map[carry->p].val == 0x90)
	{
		// printf("b\n");
		iterate(&carry->p, 1);
		n = get_uint(vm->map, carry->p);
		iterate(&carry->p, 4);
		carry->registry[vm->map[carry->p].val - 1] = n;
		carry->carry = carry->registry[vm->map[carry->p].val - 1] == 0 ? 1 : 0;
		carry->pc = iterate(&carry->p, 1);
		// printf("bb\n");
	}
	return (0);
}


// int		lld(t_carry *carry, t_vm *vm)
// {
// 	int n;

// 	iterate(&carry->pc, 1);
// 	if (vm->map[carry->pc].val == 0xd0)
// 	{
// 		n = (carry->pc + get_usrt(vm->map, carry->pc + 1)) % MEM_SIZE;
// 		carry->registry[vm->map[carry->pc + 3].val - 1] = get_uint(vm->map, n);
// 		carry->carry = carry->registry[vm->map[carry->pc + 3].val - 1] == 0 ? 1 : 0;
// 		iterate(&carry->pc, 4);
// 	}
// 	else if (vm->map[carry->pc].val == 0x90)
// 	{
// 		carry->registry[vm->map[carry->pc + 5].val - 1] = get_uint(vm->map, carry->pc + 1);
// 		carry->carry = carry->registry[vm->map[carry->pc + 5].val - 1] == 0 ? 1 : 0;
// 		iterate(&carry->pc, 6);
// 	}
// 	return (0);
// }

