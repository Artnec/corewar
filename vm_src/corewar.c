/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 21:08:49 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/08/06 21:08:50 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		finish_him(t_vm *vm)
{
	if (vm->v == 1 && vm->cycle <= vm->cycle_to_start)
	{
		start_ncurses();
		draw_ncurses(vm);
		pause_ncurses(vm);
		end_ncurses(vm);
	}
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
			vm->last, vm->bot[vm->last - 1].name);
}

static void		play_with_visualizator(t_vm *vm, clock_t *t1, clock_t *t2)
{
	key_control(vm);
	if ((int)(*t1 * vm->fps / CLOCKS_PER_SEC) <
		(int)(*t2 * vm->fps / CLOCKS_PER_SEC) || vm->s == 1)
	{
		*t1 = clock();
		run_cycle(vm);
		if (vm->processes == 0)
		{
			while ((int)(*t1 * vm->fps / CLOCKS_PER_SEC) >=
				(int)(*t2 * vm->fps / CLOCKS_PER_SEC))
			{
				key_control(vm);
				*t2 = clock();
			}
			draw_ncurses(vm);
			end_ncurses(vm);
			return ;
		}
	}
	*t2 = clock();
}

void			corewar(t_vm *vm)
{
	clock_t		t1;
	clock_t		t2;

	t1 = clock();
	t2 = clock() * CLOCKS_PER_SEC;
	while (vm->processes > 0)
	{
		if (vm->cycle == vm->cycle_to_start && vm->v == 1)
			start_ncurses();
		if (vm->dump == vm->cycle)
		{
			dump_memory(vm);
			return ;
		}
		if (vm->cycle >= vm->cycle_to_start && vm->v == 1)
			play_with_visualizator(vm, &t1, &t2);
		else
			run_cycle(vm);
	}
	finish_him(vm);
}
