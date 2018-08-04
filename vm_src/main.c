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

void	mem_zero(void *mem, int size)
{
	int		i;
	char	*c;

	c = mem;
	i = 0;
	while (i < size)
		c[i++] = 0;
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
	int i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->number_of_bots)
	{
		ft_printf("* Player %d, weighing %ld bytes, \"%s\" (\"%s\") !\n", i + 1,
			vm->bot[i].size, vm->bot[i].name, vm->bot[i].comment);
		i++;
	}
}

void	dump_memory(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%02x%02x : ", i >> 8, i & 0xff);
		ft_printf("%02x ", vm->map[i].val);
		if ((i + 1) % 64 == 0)
			write(1, "\n", 1);
		i++;
	}
}

t_lst	*add_list_head(t_lst *list_head)
{
	t_lst	*list;

	list = (t_lst *)malloc(sizeof(t_lst));
	list->next = list_head;
	return (list);
}

void	initiate_carrys_and_map(t_vm *vm)
{
	int i;
	int n;

	i = -1;
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
			if ((int)(t1 * vm->fps / CLOCKS_PER_SEC) < (int)(t2 * vm->fps / CLOCKS_PER_SEC) || vm->s == 1)
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
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->last, vm->bot[vm->last - 1].name);
}

void	initiate_structure(t_vm *vm)
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

int		main(int argc, char **argv)
{
	t_vm	vm;

	initiate_structure(&vm);
	if (argc < 2)
	{
		show_usage();
		return (0);
	}
	parse_arguments(argc, argv, &vm);
	if (vm.number_of_bots == 0)
    {
        show_usage();
        return (0);
    }
    if (vm.v == 1 && MEM_SIZE > 4096)
		exit_error("map is too big to be displayed\n");
	// ft_printf("dump: %d\nv: %d\n", vm.dump, vm.v);
	read_cor_files(&vm);
	if (vm.v != 1)
		player_introduction(&vm);
	vm.last = vm.number_of_bots;
	initiate_carrys_and_map(&vm);
	corewar(&vm);
	// system("say  -r 170 bot 2, won");
	return (0);
}
