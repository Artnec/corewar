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

void	exit_error(char *error_message)
{
	int i;

	i = 0;
	while (error_message[i])
		i++;
	write(2, "Error: ", 7);
	write(2, error_message, i);
	exit(1);
}

void	show_usage(void)
{
	write(1, "Usage:\n       ./corewar bot1.cor bot2.cor ", 43);
	write(1, "[min 1 and max 4 bots]\n", 23);
	write(1, "       to see visualization add [-v] as first argument\n", 55);
	write(1, "       to see state of the memory after specific cycle add ", 59);
	write(1, "[-dump cycle_num] as first argument\n", 36);
	write(1, "       you can change order of players by adding ", 49);
	write(1, "[-n number] before bot name\n", 28);
}

void	player_introduction(t_vm *vm)
{
	write(1, "Introducing contestants...\n", 27);
	for (int i = 0; i < vm->number_of_bots; i++)
		printf("  Player %d, weighing %ld bytes, \"%s\" (\"%s\") !\n", i + 1,
			vm->bot[i].size, vm->bot[i].name, vm->bot[i].comment);
}

void	put_octet_in_hex(int num)
{
	int c;

	c = num / 16 + ((num / 16 > 9) ? 87 : 48);
	write(1, &c, 1);
	c = num % 16 + ((num % 16 > 9) ? 87 : 48);
	write(1, &c, 1);
}

void	dump_memory(t_vm *vm)
{
	int idx;
	int i;

	idx = 0;
	while (idx < MEM_SIZE)
	{
		write(1, "0x", 2);
		put_octet_in_hex(idx >> 8);
		put_octet_in_hex(idx & 0xff);
		write(1, " : ", 3);
		i = -1;
		while (++i < 64)
		{
			put_octet_in_hex(vm->map[idx + i].val);
			if (i < 63)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
		idx += i;
	}
}

t_list	*add_list_head(t_list *list_head)
{
	t_list	*list;
	t_carry *carry;

	carry = (t_carry *)malloc(sizeof(t_carry));
	list = (t_list *)malloc(sizeof(t_list));
	list->carry = carry;
	list->next = list_head;
	return (list);
}

void	initiate_carrys_and_map(t_vm *vm)
{
	int i;
	int n;

	vm->carry_list = NULL;
	i = -1;
	while (++i < vm->number_of_bots)
	{
		vm->carry_list = add_list_head(vm->carry_list);
		vm->carry_list->carry->pc = MEM_SIZE / vm->number_of_bots * i;
		vm->carry_list->carry->cycles = -1;
		vm->carry_list->carry->alive = 1;
		vm->carry_list->carry->id = i + 1;
		for (int j = 0; j < 16; ++j)
			vm->carry_list->carry->registry[j] = 0;
		n = -1;
		while (++n < vm->bot[i].size)
		{
			vm->map[vm->carry_list->carry->pc + n].val = vm->bot[i].bot[n];
			vm->map[vm->carry_list->carry->pc + n].id = i + 1;
		}
	}
	vm->carry_list_head = vm->carry_list;
	vm->cycle = 0;
}

void	run_cycle(t_vm *vm)
{
	t_list	*list;

	list = vm->carry_list_head;
	if (vm->v == 1)
		draw_ncurses(vm);
	while (list)
	{
		// printf("%d\n", list->carry->pc);
		if (list->carry->cycles == -1)
		{
			if (vm->map[list->carry->pc].val > 0 && vm->map[list->carry->pc].val < 16)
				list->carry->cycles = g_op_tab[vm->map[list->carry->pc].val - 1].cycles;
			else
				list->carry->cycles = 0;
		}
		if (list->carry->cycles == 0)
		{
			// if (vm->map[list->carry->pc].val > 0 && vm->map[list->carry->pc].val < 16)
			if (vm->map[list->carry->pc].val == 2 || vm->map[list->carry->pc].val == 11 ||
				vm->map[list->carry->pc].val == 4 || vm->map[list->carry->pc].val == 5)
				vm->functions[vm->map[list->carry->pc].val - 1](list->carry, vm);
			else
				list->carry->pc++;
		}
		// printf("%d %d\n", list->carry->cycles, vm->cycle);
		list->carry->cycles -= 1;
		list = list->next;
	}
	vm->cycle += 1;
}

void	corewar(t_vm *vm)
{
	if (vm->v == 1)
		start_ncurses();
	while (vm->cycle < 1000)
	{
		if (vm->dump == vm->cycle)
		{
			dump_memory(vm);
			return ; 			/* mb flag to continue */
		}
		run_cycle(vm);
	}
	if (vm->v == 1)
		endwin();
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	vm.functions[3] = add;
	vm.functions[4] = sub;
	vm.functions[1] = ld;
	vm.functions[10] = sti;
	vm.v = 0;
	vm.dump = -1;
	if (argc < 2)
	{
		show_usage();
		return (0);
	}
	parse_arguments(argc, argv, &vm);
	// printf("dump: %d\nv: %d\n", vm.dump, vm.v);
	read_cor_files(&vm);
	player_introduction(&vm);
	for (int i = 0; i < MEM_SIZE; i++)
	{
		vm.map[i].id = 0;
		vm.map[i].val = 0;
	}
	initiate_carrys_and_map(&vm);
	corewar(&vm);
	// system("say  -r 170 bot 2, won");
	return (0);
}
