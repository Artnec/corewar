#include "corewar.h"

// #define ITE(x, y)	(x + y < 0 ? MEM_SIZE + (x + y) % MEM_SIZE : (x + y) % MEM_SIZE)

int			iterate(int *pc, int n)
{
	// printf("%d\n", ITE(1000, 10));
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


unsigned short	get_usrt(t_map *map, int n)
{
	if (n + 1 == MEM_SIZE)
		return (map[n].val << 8 | map[0].val);
	return (map[n].val << 8 | map[n + 1].val);
	// return (map[n].val << 8 | map[n + 1 == MEM_SIZE ? 0 : n + 1].val);
}


int				get_rdi_val(t_carry *carry, int t_rdi, int d, t_vm *vm)
{
	int num;
	// printf("j: %d\n", t_rdi);
	if (t_rdi == REG_CODE)
	{
		// printf("T_REG\n");
		num = carry->registry[vm->map[carry->p].val - 1];
		// printf("reg: %d\n", num);
		iterate(&carry->p, 1);
		return (num);
	}
	if (t_rdi == DIR_CODE)
	{
		// printf("T_DIR\n");
		num = d == 2 ? get_usrt(vm->map, carry->p) : get_uint(vm->map, carry->p);
		// printf("dir: %d\n", num);
		iterate(&carry->p, d);
		return (num);
	}
	if (t_rdi == IND_CODE)
	{
		// printf("T_IND\n");
		num = get_uint(vm->map, carry->pc + get_usrt(vm->map, carry->p) % IDX_MOD);
		// printf("ind: %d\n", num);
		iterate(&carry->p, 2);
		return (num);
	}
	// error ???
	return (0);
}


void			uint_to_map(unsigned int n, int id, t_map *map, int i)
{
	i %= MEM_SIZE;
	if (i < 0)
		i += MEM_SIZE;
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
