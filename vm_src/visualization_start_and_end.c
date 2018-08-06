/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_start_and_end.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 20:44:47 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/08/06 20:44:49 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		draw_border(void)
{
	int n;

	n = -1;
	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 4, 199, "Cycles/second limit :");
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

void			end_ncurses(t_vm *vm)
{
	int w;

	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 25 + vm->number_of_bots * 4, 199, "The winner is :");
	w = vm->last - 1;
	wattron(stdscr, COLOR_PAIR(w + 1));
	mvwprintw(stdscr, 25 + vm->number_of_bots * 4, 215, "%.37s",
		vm->bot[w].name);
	wattroff(stdscr, COLOR_PAIR(w + 1));
	mvwprintw(stdscr, 27 + vm->number_of_bots * 4, 199,
		"Press any key to finish");
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
	wrefresh(stdscr);
	while ((getch()) <= 0)
		;
	endwin();
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
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_RED);
	init_pair(14, COLOR_WHITE, COLOR_CYAN);
	draw_border();
}
