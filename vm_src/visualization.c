/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:46:23 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/12 20:46:25 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		draw_carrys(t_vm *vm)
{
	t_list	*tmp;
	int 	i;
	int 	j;

	tmp = vm->carry_list_head;
	while (tmp)
	{
		wattron(stdscr, COLOR_PAIR(vm->map[tmp->pc].id + 5));
		i = tmp->pc / 64 + 2;
		j = tmp->pc % 64 * 3 + 3;
		mvwprintw(stdscr, i, j, "%02x", vm->map[tmp->pc].val);
		wattroff(stdscr, COLOR_PAIR(vm->map[tmp->pc].id + 5));
		tmp = tmp->next;
	}
}

void			pause_ncurses(void)
{
	// mvwprintw(stdscr, 40, 199, "%d", getch());
	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 2, 199, "** PAUSED  **");
	while (getch() != 32)
		;
	mvwprintw(stdscr, 2, 199, "** RUNNING **");
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
}

void			draw_info(t_vm *vm)
{
	int n;

	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 4, 199, "Cycles/second limit : 50");
	mvwprintw(stdscr, 7, 199, "Cycle : %d", vm->cycle);
	mvwprintw(stdscr, 9, 199, "Processes : %d", vm->processes);
	for (n = 0; n < vm->number_of_bots; ++n)
	{
		mvwprintw(stdscr, 11 + n * 4, 199, "Player %d :", -(n + 1));
		wattron(stdscr, COLOR_PAIR(n + 1));
		mvwprintw(stdscr, 11 + n * 4, 211, "%.41s", vm->bot[n].name);
		wattroff(stdscr, COLOR_PAIR(n + 1));
		mvwprintw(stdscr, 12 + n * 4, 201, "Last live : %21d", 0);
		mvwprintw(stdscr, 13 + n * 4, 201, "Lives in current period : %7d", 0);
	}
	mvwprintw(stdscr, 17 + n * 4, 199, "CYCLE_TO_DIE : %d", vm->cycle_to_die);
	mvwprintw(stdscr, 19 + n * 4, 199, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(stdscr, 21 + n * 4, 199, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(stdscr, 23 + n * 4, 199, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
}

void			draw_ncurses(t_vm *vm)
{
	int		i;
	int		n;
	int		j;

	j = 0;
	n = 1;
	if (getch() == 32)
		pause_ncurses();
	while (++n < 66)
	{
		i = 3;
		while (i < 195)
		{
			if (vm->map[j].bold > 0)
				wattron(stdscr, A_BOLD);
			wattron(stdscr, COLOR_PAIR(vm->map[j].id));
			mvwprintw(stdscr, n, i, "%02x", vm->map[j].val);
			if (vm->map[j].bold > 0 && vm->map[j].bold--)
				wattroff(stdscr, A_BOLD);
			wattroff(stdscr, COLOR_PAIR(vm->map[j++].id));
			i += 3;
		}
	}
	draw_carrys(vm);
	draw_info(vm);
	wrefresh(stdscr);
	if (vm->cycle == 0)
		pause_ncurses();
	usleep(20000);
}

static void		draw_border(void)
{
	int n;

	n = -1;
	wattron(stdscr, A_BOLD | COLOR_PAIR(4));
	mvwprintw(stdscr, 2, 215, "***********************************");
	wattroff(stdscr, A_BOLD | COLOR_PAIR(4));
	wattron(stdscr, COLOR_PAIR(100));
	while (++n < 68)
	{
		mvwprintw(stdscr, n, 0, " ");
		mvwprintw(stdscr, n, 253, " ");
		mvwprintw(stdscr, n, 196, " ");
	}
	n = -1;
	while (++n < 253)
	{
		mvwprintw(stdscr, 0, n, " ");
		mvwprintw(stdscr, 67, n, " ");
	}
	wattroff(stdscr, COLOR_PAIR(100));
}

void			start_ncurses(void)
{
	initscr();
	keypad(stdscr, true);
	noecho();
	timeout(0);
	cbreak();
	curs_set(false);
	start_color();
	init_color(COLOR_WHITE, 450, 450, 450);
	init_pair(100, COLOR_WHITE, COLOR_WHITE);
	init_pair(50, COLOR_WHITE, COLOR_BLACK);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	draw_border();
}
