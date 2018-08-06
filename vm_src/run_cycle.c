/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:28:46 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/04 22:28:47 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		delete_dead_processes(t_lst *carry, t_lst *prev_carry, t_vm *vm)
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

void			check_bot_alive(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->number_of_bots)
	{
		if (vm->bot[i].last_live < vm->cycle - (int)vm->cycle_to_die)
			vm->bot[i].alive = 0;
		else
			vm->bot[i].alive = 1;
	}
}

void			change_cycle_to_die(t_vm *vm)
{
	if (vm->checks_count == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks_count = 0;
	}
	else if (vm->lives_in_cycle >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks_count = 0;
	}
}

static void		check_processes(t_vm *vm)
{
	int		i;
	t_lst	*carry;

	vm->checks_count++;
	delete_dead_processes(vm->carry_list_head, NULL, vm);
	check_bot_alive(vm);
	if (vm->processes == 0)
		vm->carry_list_head = NULL;
	carry = vm->carry_list_head;
	while (carry)
	{
		carry->alive = 0;
		carry = carry->next;
	}
	change_cycle_to_die(vm);
	vm->lives_in_cycle = 0;
	i = 0;
	while (i < vm->number_of_bots)
		vm->bot[i++].lives_in_cycle = 0;
	vm->cycle_alive = 0;
}

static void		cycle_loop(t_lst *carry, t_vm *vm)
{
	if (carry->opcode == -1 && IS_VALID_OPCODE(vm->map[carry->pc].val))
	{
		carry->opcode = vm->map[carry->pc].val - 1;
		carry->cycles = g_op_tab[carry->opcode].cycles;
	}
	else if (carry->opcode == -1)
		iterate(&carry->pc, 1);
	else if (carry->cycles == 1)
	{
		if (check_codage_and_regs(carry, vm))
			vm->functions[carry->opcode](carry, vm);
		carry->opcode = -1;
	}
	carry->cycles -= 1;
}

void			run_cycle(t_vm *vm)
{
	t_lst	*carry;

	carry = vm->carry_list_head;
	if (vm->v == 1 && vm->cycle >= vm->cycle_to_start)
		draw_ncurses(vm);
	if ((int)vm->cycle_to_die <= 0)
		delete_dead_processes(vm->carry_list_head, NULL, vm);
	while (carry && (int)vm->cycle_to_die > 0)
	{
		// if (vm->cycle == 12334 && carry->cycles == 1)
		// 	printf("%d\n", carry->pc);
		cycle_loop(carry, vm);
		carry = carry->next;
	}
	vm->cycle_alive += 1;
	if (vm->cycle != 0 && vm->cycle_alive == vm->cycle_to_die)
		check_processes(vm);
	vm->cycle += 1;
}
