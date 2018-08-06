/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_draw_ncurses.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 20:43:27 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/08/06 20:43:29 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			draw_carrys(t_vm *vm)
{
	t_lst	*tmp;
	int		i;
	int		j;

	tmp = vm->carry_list_head;
	while (tmp)
	{
		if (vm->map[tmp->pc].bold > 0)
			wattron(stdscr, A_BOLD);
		if (vm->map[tmp->pc].live <= 0)
		{
			wattron(stdscr, COLOR_PAIR(vm->map[tmp->pc].id + 5));
			i = tmp->pc / 64 + 2;
			j = tmp->pc % 64 * 3 + 3;
			mvwprintw(stdscr, i, j, "%02x", vm->map[tmp->pc].val);
			wattroff(stdscr, COLOR_PAIR(vm->map[tmp->pc].id + 5));
		}
		if (vm->map[tmp->pc].bold > 0)
			wattroff(stdscr, A_BOLD);
		tmp = tmp->next;
	}
}

static void			draw_info(t_vm *vm)
{
	int n;

	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 4, 221, "%d      ", vm->fps);
	mvwprintw(stdscr, 7, 199, "Cycle : %d", vm->cycle);
	mvwprintw(stdscr, 9, 199, "Processes : %d      ", vm->processes);
	n = -1;
	while (++n < vm->number_of_bots)
	{
		mvwprintw(stdscr, 11 + n * 4, 199, "Player %d :", -(n + 1));
		wattron(stdscr, COLOR_PAIR(n + 1));
		mvwprintw(stdscr, 11 + n * 4, 211, "%.41s", vm->bot[n].name);
		wattroff(stdscr, COLOR_PAIR(n + 1));
		mvwprintw(stdscr, 12 + n * 4, 201, "Last live : %21d",
			vm->bot[n].last_live);
		mvwprintw(stdscr, 13 + n * 4, 201, "Lives in current period : %7d",
			vm->bot[n].lives_in_cycle);
	}
	mvwprintw(stdscr, 13 + n * 4, 199, "CYCLE_TO_DIE : %u    ",
		vm->cycle_to_die);
	mvwprintw(stdscr, 15 + n * 4, 199, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(stdscr, 16 + n * 4, 199, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(stdscr, 19 + n * 4, 199, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
}

static void			print_the_row(t_vm *vm, int *j, int n, int *i)
{
	while (*i < 195 && ((n - 2) * 64 + (*i / 3)) <= MEM_SIZE)
	{
		if (vm->map[*j].bold > 0 || vm->map[*j].live > 0)
			wattron(stdscr, A_BOLD);
		if (vm->map[*j].live > 0)
			wattron(stdscr, COLOR_PAIR(vm->map[*j].live_id + 10));
		else
			wattron(stdscr, COLOR_PAIR(vm->map[*j].id));
		mvwprintw(stdscr, n, *i, "%02x", vm->map[*j].val);
		if ((vm->map[*j].bold > 0 && vm->map[*j].bold--) ||
			vm->map[*j].live > 0)
			wattroff(stdscr, A_BOLD);
		if (vm->map[*j].live > 0)
		{
			vm->map[*j].live--;
			wattroff(stdscr, COLOR_PAIR(vm->map[(*j)++].live_id + 10));
		}
		else
			wattroff(stdscr, COLOR_PAIR(vm->map[(*j)++].id));
		*i += 3;
	}
}

void				draw_ncurses(t_vm *vm)
{
	int		i;
	int		n;
	int		j;

	j = 0;
	n = 1;
	while (++n < MEM_SIZE / 64 + 3 && (n - 2) * 64 != MEM_SIZE)
	{
		i = 3;
		print_the_row(vm, &j, n, &i);
	}
	draw_carrys(vm);
	draw_info(vm);
	wrefresh(stdscr);
	if (vm->cycle == vm->cycle_to_start)
		pause_ncurses(vm);
}
