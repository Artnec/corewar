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
		wattron(stdscr, COLOR_PAIR(vm->map[tmp->carry->pc].id + 5));
		i = tmp->carry->pc / 64 + 2;
		j = tmp->carry->pc % 64 * 3 + 3;
		mvwprintw(stdscr, i, j, "%02x", vm->map[tmp->carry->pc].val);
		wattroff(stdscr, COLOR_PAIR(vm->map[tmp->carry->pc].id + 5));
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
	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 4, 199, "Cycles/second limit : 50");
	mvwprintw(stdscr, 7, 199, "Cycle : %d", vm->cycle);
	mvwprintw(stdscr, 9, 199, "Processes : %d", vm->number_of_bots);
	mvwprintw(stdscr, 21, 199, "CYCLE_TO_DIE : %d", 1536);
	mvwprintw(stdscr, 23, 199, "CYCLE_DELTA : %d", 50);
	mvwprintw(stdscr, 25, 199, "NBR_LIVE : %d", 21);
	mvwprintw(stdscr, 27, 199, "MAX_CHECKS : %d", 10);
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
			wattron(stdscr, COLOR_PAIR(vm->map[j].id));
			mvwprintw(stdscr, n, i, "%02x", vm->map[j].val);
			wattroff(stdscr, COLOR_PAIR(vm->map[j++].id));
			i += 3;
		}
	}
	draw_carrys(vm);
	draw_info(vm);
	wrefresh(stdscr);
	if (vm->cycle == 0)
		pause_ncurses();
	usleep(50000);
}

static void		draw_border(void)
{
	int n;

	n = -1;
	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 2, 199, "** RUNNING **");
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
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
