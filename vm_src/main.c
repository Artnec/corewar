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
		printf("* Player %d, weighing %ld bytes, \"%s\" (\"%s\") !\n", i + 1,
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
			// if (i < 63)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
		idx += i;
	}
}

t_list	*add_list_head(t_list *list_head)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->next = list_head;
	return (list);
}

void	initiate_carrys_and_map(t_vm *vm)
{
	int i;
	int n;

	vm->carry_list_head = NULL;
	i = -1;
	vm->processes = vm->number_of_bots;
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
		for (int j = 1; j < REG_NUMBER; ++j)
			vm->carry_list_head->registry[j] = 0;
		n = -1;
		while (++n < vm->bot[i].size)
		{
			vm->map[vm->carry_list_head->pc + n].val = vm->bot[i].bot[n];
			vm->map[vm->carry_list_head->pc + n].id = i + 1;
		}
	}
}

int		check_opcode_with_codage(int op, int p, t_list *carry, t_vm *vm)
{
	int i;
	int error;
	int c;

	error = 0;
	i = -1;
	while (++i < g_op_tab[op].args_num)
	{
		c = (carry->codage >> (4 - i * 2)) & 3;
		if (c == REG_CODE)
		{
			if (!(g_op_tab[op].args[i] & T_REG) || REG_CHECK(vm->map[p].val))
				error = 1;
			iterate(&p, 1);
		}
		else if (c == DIR_CODE)
		{
			if ((g_op_tab[op].args[i] & T_DIR) == 0)
				error = 1;
			iterate(&p, g_op_tab[op].label_size == 1 ? 2 : 4);
		}
		else if (c == IND_CODE)
		{
			if ((g_op_tab[op].args[i] & T_IND) == 0)
				error = 1;
			iterate(&p, 2);
		}
		else
			error = 1;
	}
	if (error == 1)
		carry->pc = p;
	return (error);
}

int		check_codage_and_regs(t_list *carry, t_vm *vm)
{
	int error;
	int op;

	error = 0;
	carry->op = carry->pc;
	op = carry->opcode;
	iterate(&carry->pc, 1);
	if (g_op_tab[op].codage == 1)
	{
		carry->codage = vm->map[carry->pc].val >> 2;
		iterate(&carry->pc, 1);
		error = check_opcode_with_codage(op, carry->pc, carry, vm);
	}
	else if (g_op_tab[op].args[0] == T_REG && (error = REG_CHECK(vm->map[carry->pc].val)))
		iterate(&carry->pc, 1);
	return (error == 0);
}

void	delete_dead_processes(t_list *carry, t_list *prev_carry, t_vm *vm)
{
	while (carry)
	{
		if (carry->alive == 0 || (int)vm->cycle_to_die <= 0)
		{
			if (prev_carry == NULL)
			{
				vm->carry_list_head = vm->carry_list_head->next;
				free(carry);
				carry = vm->carry_list_head;
			}
			else
			{
				carry = carry->next;
				free(prev_carry->next);
				prev_carry->next = carry;
			}
			vm->processes -= 1;
		}
		else
		{
			prev_carry = carry;
			carry = carry->next;
		}
	}
}

void	check_processes(t_vm *vm)
{
	int		i;
	t_list	*carry;

	vm->checks_count++;
	delete_dead_processes(vm->carry_list_head, NULL, vm);
	if (vm->processes == 0)
		vm->carry_list_head = NULL;
	carry = vm->carry_list_head;
	while (carry)
	{
		carry->alive = 0;
		carry = carry->next;
	}
	if (vm->checks_count == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks_count = 0;
	}
	else if (vm->lives_in_cycle >= NBR_LIVE)
		vm->cycle_to_die -= CYCLE_DELTA;
	vm->lives_in_cycle = 0;
	i = 0;
	while (i < vm->number_of_bots)
		vm->bot[i++].lives_in_cycle = 0;
	vm->cycle_alive = 0;
}

void	run_cycle(t_vm *vm)
{
	t_list	*carry;

	carry = vm->carry_list_head;
	if (vm->v == 1)
		draw_ncurses(vm);
	if ((int)vm->cycle_to_die <= 0)
		delete_dead_processes(vm->carry_list_head, NULL, vm);
	while (carry && (int)vm->cycle_to_die > 0)
	{
		if (carry->opcode == -1 && IS_VALID_OPCODE(vm->map[carry->pc].val))
		{
			carry->opcode = vm->map[carry->pc].val - 1;
			carry->cycles = g_op_tab[carry->opcode].cycles;
		}
		else if (carry->opcode == -1)
			iterate(&carry->pc, 1);
		if (carry->cycles == 1)
		{
			if (check_codage_and_regs(carry, vm))
				vm->functions[carry->opcode](carry, vm);
			carry->opcode = -1;
		}
		carry->cycles -= 1;
		carry = carry->next;
	}
	vm->cycle_alive += 1;
	if (vm->cycle != 0 && vm->cycle_alive == vm->cycle_to_die)
		check_processes(vm);
	vm->cycle += 1;
}

void	corewar(t_vm *vm)
{
	clock_t		t1;
	clock_t		t2;

	t1 = clock();
	t2 = clock() * CLOCKS_PER_SEC;
	if (vm->v == 1)
		start_ncurses();
	while (vm->processes > 0)
	{
		if (vm->dump == vm->cycle)
		{
			dump_memory(vm);
			return ;
		}
		if (vm->v == 1)
		{
			key_control(vm);
			if ((int)(t1 * vm->fps / CLOCKS_PER_SEC) < (int)(t2 * vm->fps / CLOCKS_PER_SEC))
			{
				t1 = clock();
				run_cycle(vm);
				if (vm->processes == 0 )
				{
					while ((int)(t1 * vm->fps / CLOCKS_PER_SEC) >= (int)(t2 * vm->fps / CLOCKS_PER_SEC))
					{
						key_control(vm);
						t2 = clock();
					}
					draw_ncurses(vm);
					end_ncurses(vm);
					return ;
				}
			}
			t2 = clock();
		}
		else
			run_cycle(vm);
	}
	int w = get_winner(vm);
	printf("Contestant %d, \"%s\", has won !\n", w + 1, vm->bot[w].name);
}

void	initiate_structure(t_vm *vm)
{
	vm->functions[0] = &live;
	vm->functions[1] = &ld;
	vm->functions[2] = &st;
	vm->functions[3] = &add;
	vm->functions[4] = &sub;
	vm->functions[5] = &and;
	vm->functions[6] = &or;
	vm->functions[7] = &xor;
	vm->functions[8] = &zjmp;
	vm->functions[9] = &ldi;
	vm->functions[10] = &sti;
	vm->functions[11] = &fork_op;
	vm->functions[12] = &lld;
	vm->functions[13] = &lldi;
	vm->functions[14] = &lfork;
	vm->functions[15] = &aff;
	vm->v = 0;
	vm->dump = -1;
	vm->lives_in_cycle = 0;
	vm->checks_count = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	for (int i = 0; i < MEM_SIZE; i++)
	{
		vm->map[i].id = 0;
		vm->map[i].val = 0;
		vm->map[i].bold = 0;
	}
	vm->fps = 50;
	vm->cycle = 0;
	vm->cycle_alive = 0;
}

int		get_winner(t_vm *vm)
{
	int i;
	int m;
	int b;

	m = -1;
	i = vm->number_of_bots;
	while (--i >= 0)
	{
		if (vm->bot[i].last_live > m)
		{
			m = vm->bot[i].last_live;
			b = i;
		}
	}
	i = -1;
	while (++i < vm->number_of_bots)
	{
		if (!strcmp(vm->bot[i].name, vm->bot[b].name) &&
			vm->bot[i].last_live == vm->bot[b].last_live) // !!!!!!!!!!!!!!!!!!!!!!! STRCMP -> FT_STRCMP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! -42
			return (i);
	}
	return (b);
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	setbuf(stdout, NULL);
	initiate_structure(&vm);
	if (argc < 2)
	{
		show_usage();
		return (0);
	}
	parse_arguments(argc, argv, &vm);
	// printf("dump: %d\nv: %d\n", vm.dump, vm.v);
	read_cor_files(&vm);
	if (vm.v != 1)
		player_introduction(&vm);
	initiate_carrys_and_map(&vm);
	corewar(&vm);
	// system("say  -r 170 bot 2, won");
	return (0);
}
