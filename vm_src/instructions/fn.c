/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:38:36 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/08/06 18:38:39 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	get_uint(t_map *map, int n)
{
	if (n + 3 >= MEM_SIZE)
	{
		if (n == 4339)
			ft_printf("%d\n", n);
		return (map[n].val << 24 | map[(n + 1) % MEM_SIZE].val << 16 |
			map[(n + 2) % MEM_SIZE].val << 8 | map[(n + 3) % MEM_SIZE].val);
	}
	return (map[n].val << 24 | map[n + 1].val << 16 |
		map[n + 2].val << 8 | map[n + 3].val);
}

short			get_short(t_map *map, int n)
{
	return (map[n].val << 8 | (map[n + 1 == MEM_SIZE ? 0 : n + 1].val));
}

int				get_rdi_val(t_lst *carry, int t_rdi, int d, t_vm *vm)
{
	int num;

	if (t_rdi == REG_CODE)
	{
		num = carry->registry[vm->map[carry->pc].val - 1];
		iterate(&carry->pc, 1);
		return (num);
	}
	if (t_rdi == DIR_CODE)
	{
		num = d == 2 ? (short)get_short(vm->map, carry->pc) :
			get_uint(vm->map, carry->pc);
		iterate(&carry->pc, d);
		return (num);
	}
	if (t_rdi == IND_CODE)
	{
		num = carry->op;
		iterate(&num, get_short(vm->map, carry->pc) % IDX_MOD);
		num = get_uint(vm->map, num);
		iterate(&carry->pc, 2);
		return (num);
	}
	return (0);
}

void			uint_to_map(unsigned int n, int id, t_vm *vm, int i)
{
	i %= MEM_SIZE;
	if (i < 0)
		i += MEM_SIZE;
	vm->map[i].val = (n & 0xff000000) >> 24;
	vm->map[i].id = id;
	vm->map[(i + 1) % MEM_SIZE].val = (n & 0x00ff0000) >> 16;
	vm->map[(i + 1) % MEM_SIZE].id = id;
	vm->map[(i + 2) % MEM_SIZE].val = (n & 0x0000ff00) >> 8;
	vm->map[(i + 2) % MEM_SIZE].id = id;
	vm->map[(i + 3) % MEM_SIZE].val = (n & 0x000000ff);
	vm->map[(i + 3) % MEM_SIZE].id = id;
	if (vm->cycle >= vm->cycle_to_start)
	{
		vm->map[i].bold = 49;
		vm->map[(i + 1) % MEM_SIZE].bold = 49;
		vm->map[(i + 2) % MEM_SIZE].bold = 49;
		vm->map[(i + 3) % MEM_SIZE].bold = 49;
	}
	else if (vm->cycle >= vm->cycle_to_start - 49)
	{
		vm->map[i].bold = vm->cycle - vm->cycle_to_start + 50;
		vm->map[(i + 1) % MEM_SIZE].bold = vm->cycle - vm->cycle_to_start + 50;
		vm->map[(i + 2) % MEM_SIZE].bold = vm->cycle - vm->cycle_to_start + 50;
		vm->map[(i + 3) % MEM_SIZE].bold = vm->cycle - vm->cycle_to_start + 50;
	}
}

void			fork_carry(t_lst *orig_carry, t_vm *vm, int pos)
{
	t_lst	*carry;
	int		n;

	carry = (t_lst *)malloc(sizeof(t_lst));
	carry->next = vm->carry_list_head;
	vm->carry_list_head = carry;
	carry->pc = orig_carry->op;
	iterate(&carry->pc, pos);
	carry->cycles = -1;
	carry->opcode = -1;
	carry->carry = orig_carry->carry;
	carry->alive = orig_carry->alive;
	carry->id = orig_carry->id;
	n = -1;
	while (++n < REG_NUMBER)
		carry->registry[n] = orig_carry->registry[n];
}
