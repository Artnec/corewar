#include "corewar.h"

int			iterate(int *pc, int n)
{
	if (*pc + n < 0)
	{
		*pc = MEM_SIZE + (*pc + n) % MEM_SIZE;
		return (*pc);
	}
	*pc = (*pc + n) % MEM_SIZE;
	return (*pc);
}

unsigned int	get_uint(t_map *map, int n)
{
	if (n + 3 >= MEM_SIZE)
	{
		return (map[n].val << 24 | map[(n + 1) % MEM_SIZE].val << 16 |
			map[(n + 2) % MEM_SIZE].val << 8 | map[(n + 3) % MEM_SIZE].val);
	}
	return (map[n].val << 24 | map[n + 1].val << 16 | map[n + 2].val << 8 | map[n + 3].val);
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
		// printf("T_REG\n");
		num = carry->registry[vm->map[carry->pc].val - 1];
		// printf("reg: %d\n", num);
		iterate(&carry->pc, 1);
		return (num);
	}
	if (t_rdi == DIR_CODE)
	{
		// printf("T_DIR\n");
		num = d == 2 ? (short)get_short(vm->map, carry->pc) : get_uint(vm->map, carry->pc);
		// printf("dir: %d\n", num);
		iterate(&carry->pc, d);
		return (num);
	}
	if (t_rdi == IND_CODE)
	{
		// printf("T_IND\n");
		num = get_uint(vm->map, carry->op + get_short(vm->map, carry->pc) % IDX_MOD);
		// printf("ind: %d\n", num);
		iterate(&carry->pc, 2);
		return (num);
	}
	// error ???
	return (0);
}

void			uint_to_map(unsigned int n, int id, t_map *map, int i)
{
	i %= MEM_SIZE;  // is needed ?
	if (i < 0)
		i += MEM_SIZE;  // is needed ?
	map[i].val = (n & 0xff000000) >> 24;
	map[i].id = id;
	map[i].bold = 50;
	map[(i + 1) % MEM_SIZE].val = (n & 0x00ff0000) >> 16;
	map[(i + 1) % MEM_SIZE].id = id;
	map[(i + 1) % MEM_SIZE].bold = 50;
	map[(i + 2) % MEM_SIZE].val = (n & 0x0000ff00) >> 8;
	map[(i + 2) % MEM_SIZE].id = id;
	map[(i + 2) % MEM_SIZE].bold = 50;
	map[(i + 3) % MEM_SIZE].val = (n & 0x000000ff);
	map[(i + 3) % MEM_SIZE].id = id;
	map[(i + 3) % MEM_SIZE].bold = 50;
}

void	fork_carry(t_lst *orig_carry, t_vm *vm, int pos)
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
