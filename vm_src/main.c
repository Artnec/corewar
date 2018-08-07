/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:50:01 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/22 17:50:03 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		mem_zero(void *mem, int size)
{
	int		i;
	char	*c;

	c = mem;
	i = 0;
	while (i < size)
		c[i++] = 0;
}

static t_lst	*add_list_head(t_lst *list_head)
{
	t_lst	*list;

	list = (t_lst *)malloc(sizeof(t_lst));
	list->next = list_head;
	return (list);
}

static void		initiate_carrys_and_map(t_vm *vm, int i, int n)
{
	while (++i < vm->number_of_bots)
	{
		vm->carry_list_head = add_list_head(vm->carry_list_head);
		vm->carry_list_head->pc = MEM_SIZE / vm->number_of_bots * i;
		vm->carry_list_head->cycles = 0;
		vm->carry_list_head->alive = 0;
		vm->carry_list_head->id = i + 1;
		vm->carry_list_head->registry[0] = -(i + 1);
		vm->carry_list_head->opcode = -1;
		vm->bot[i].lives_in_cycle = 0;
		vm->bot[i].last_live = 0;
		n = 1;
		while (n < REG_NUMBER)
			vm->carry_list_head->registry[n++] = 0;
		n = -1;
		while (++n < vm->bot[i].size)
		{
			vm->map[vm->carry_list_head->pc + n].val = vm->bot[i].bot[n];
			vm->map[vm->carry_list_head->pc + n].id = i + 1;
		}
	}
	vm->processes = vm->number_of_bots;
}

static void		initiate_structure(t_vm *vm)
{
	mem_zero(vm, sizeof(*vm));
	vm->functions[0] = live;
	vm->functions[1] = ld;
	vm->functions[2] = st;
	vm->functions[3] = add;
	vm->functions[4] = sub;
	vm->functions[5] = and;
	vm->functions[6] = or;
	vm->functions[7] = xor;
	vm->functions[8] = zjmp;
	vm->functions[9] = ldi;
	vm->functions[10] = sti;
	vm->functions[11] = fork_op;
	vm->functions[12] = lld;
	vm->functions[13] = lldi;
	vm->functions[14] = lfork;
	vm->functions[15] = aff;
	vm->dump = -1;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->fps = 50;
}

int				main(int argc, char **argv)
{
	t_vm	vm;

	initiate_structure(&vm);
	if (argc < 2)
	{
		show_usage();
		return (0);
	}
	parse_arguments(argc, argv, &vm, -1);
	if (vm.number_of_bots == 0)
	{
		show_usage();
		return (0);
	}
	if (vm.v == 1 && MEM_SIZE > 4096)
		exit_error("map is too big to be displayed\n");
	read_cor_files(&vm);
	if (vm.v != 1)
		player_introduction(&vm);
	initiate_carrys_and_map(&vm, -1, 0);
	sound_stuff(&vm, 0);
	corewar(&vm);
	sound_stuff(&vm, 1);
	return (0);
}
