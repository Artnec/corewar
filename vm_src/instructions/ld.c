/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 21:14:14 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/24 21:14:15 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	get_uint(t_map *map)
{
	return (map[0].val << 24 | map[1].val << 16 | map[2].val << 8 | map[3].val);
}

unsigned short	get_usrt(t_map *map)
{
	return (map[0].val << 8 | map[1].val);
}

void			uint_to_map(unsigned int n, int id, t_map *map)
{
	map[0].val = (n & 0xff000000) >> 24;
	map[0].id = id;
	map[1].val = (n & 0x00ff0000) >> 16;
	map[1].id = id;
	map[2].val = (n & 0x0000ff00) >> 8;
	map[2].id = id;
	map[3].val = (n & 0x000000ff);
	map[3].id = id;
}

int		ld(t_carry *carry, t_vm *vm)
{
	// printf("ld\n");
	// printf("map %02x\n", vm->map[carry->pc + 1].val);
	carry->pc++;
	if (vm->map[carry->pc].val == 0xd0)
	{
		int n = (carry->pc + get_usrt(vm->map + carry->pc + 1) % IDX_MOD) % MEM_SIZE;
		carry->registry[vm->map[carry->pc + 3].val] = get_uint(vm->map + n);
		// printf("%d %d\n", vm->map[carry->pc + 3].val, carry->registry[vm->map[carry->pc + 3].val]);
		// printf("indirect %u\n", carry->registry[vm->map[carry->pc + 3].val]);
		carry->carry = carry->registry[vm->map[carry->pc + 3].val] == 0 ? 1 : 0;
		carry->pc += 4;
	}
	else if (vm->map[carry->pc].val == 0x90)
	{
		carry->registry[vm->map[carry->pc + 5].val] = get_uint(vm->map + carry->pc + 1);
		// printf("%d %d\n", vm->map[carry->pc + 5].val, carry->registry[vm->map[carry->pc + 5].val]);
		// printf("direct %u\n", carry->registry[vm->map[carry->pc + 5].val]);
		carry->carry = carry->registry[vm->map[carry->pc + 5].val] == 0 ? 1 : 0;
		carry->pc += 6;
	}

	// (void)vm;
	// (void)carry;
	return (0);
}
