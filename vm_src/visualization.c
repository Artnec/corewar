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
	t_lst	*tmp;
	int 	i;
	int 	j;

	tmp = vm->carry_list_head;
	while (tmp)
	{
		if (vm->map[tmp->pc].live <= 0)
		{
			wattron(stdscr, COLOR_PAIR(vm->map[tmp->pc].id + 5));
			i = tmp->pc / 64 + 2;
			j = tmp->pc % 64 * 3 + 3;
			mvwprintw(stdscr, i, j, "%02x", vm->map[tmp->pc].val);
			wattroff(stdscr, COLOR_PAIR(vm->map[tmp->pc].id + 5));
		}
		tmp = tmp->next;
	}
}

void			pause_ncurses(t_vm *vm)
{
	int		k;

	// mvwprintw(stdscr, 40, 199, "%d", getch());
	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 2, 199, "** PAUSED  **");
	while ((k = getch()))
	{
		if (k == 113)
			vm->fps = (vm->fps > 10 ? vm->fps - 10 : 1);
		else if (k == 119)
			vm->fps -= (vm->fps > 1 ? 1 : 0);
		else if (k == 101)
			vm->fps += (vm->fps == 1000 ? 0 : 1);
		else if (k == 114)
			vm->fps = (vm->fps > 990 ? 1000 : vm->fps + 10);
		else if (k == 115)
		{
			vm->s = 1;
			break ;
		}
		else if (k == 32)
			break ;
		mvwprintw(stdscr, 4, 221, "%d      ", vm->fps);
	}
	mvwprintw(stdscr, 2, 199, "** RUNNING **");
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
}

void			draw_info(t_vm *vm)
{
	int n;

	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 4, 221, "%d      ", vm->fps);
	mvwprintw(stdscr, 7, 199, "Cycle : %d", vm->cycle);
	mvwprintw(stdscr, 9, 199, "Processes : %d      ", vm->processes);
	for (n = 0; n < vm->number_of_bots; ++n)
	{
		mvwprintw(stdscr, 11 + n * 4, 199, "Player %d :", -(n + 1));
		wattron(stdscr, COLOR_PAIR(n + 1));
		mvwprintw(stdscr, 11 + n * 4, 211, "%.41s", vm->bot[n].name);
		wattroff(stdscr, COLOR_PAIR(n + 1));
		mvwprintw(stdscr, 12 + n * 4, 201, "Last live : %21d", vm->bot[n].last_live);
		mvwprintw(stdscr, 13 + n * 4, 201, "Lives in current period : %7d", vm->bot[n].lives_in_cycle);
	}
	mvwprintw(stdscr, 17 + n * 4, 199, "CYCLE_TO_DIE : %u    ", vm->cycle_to_die);
	mvwprintw(stdscr, 19 + n * 4, 199, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(stdscr, 21 + n * 4, 199, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(stdscr, 23 + n * 4, 199, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
}

void			key_control(t_vm *vm)
{
	int		k;

	if (vm->s == 1)
	{
		vm->s = 0;
		pause_ncurses(vm);
		return ;
	}
	k = getch();
	if (k == 113)
		vm->fps = (vm->fps > 10 ? vm->fps - 10 : 1);
	else if (k == 119)
		vm->fps -= (vm->fps > 1 ? 1 : 0);
	else if (k == 101)
		vm->fps += (vm->fps < 1000 ? 1 : 0);
	else if (k == 114)
		vm->fps = (vm->fps < 990 ? vm->fps + 10 : 1000);
	else if (k == 32)
		pause_ncurses(vm);
}

void			draw_ncurses(t_vm *vm)
{
	int		i;
	int		n;
	int		j;

	j = 0;
	n = 1;
	// if (getch() == 32)
	// 	pause_ncurses(vm);
	while (++n < 66)
	{
		i = 3;
		while (i < 195)
		{
			if (vm->map[j].bold > 0 || vm->map[j].live > 0)
				wattron(stdscr, A_BOLD);
			if (vm->map[j].live > 0)
				wattron(stdscr, COLOR_PAIR(vm->map[j].live_id + 10));
			else
				wattron(stdscr, COLOR_PAIR(vm->map[j].id));
			mvwprintw(stdscr, n, i, "%02x", vm->map[j].val);
			if ((vm->map[j].bold > 0 && vm->map[j].bold--) || vm->map[j].live > 0)
				wattroff(stdscr, A_BOLD);
			if (vm->map[j].live > 0)
			{
				vm->map[j].live--;
				wattroff(stdscr, COLOR_PAIR(vm->map[j++].live_id + 10));
			}
			else
				wattroff(stdscr, COLOR_PAIR(vm->map[j++].id));
			i += 3;
		}
	}
	draw_carrys(vm);
	draw_info(vm);
	wrefresh(stdscr);
	if (vm->cycle == 0)
		pause_ncurses(vm);
	// usleep(20000);
}

static void		draw_border(void)
{
	int n;

	n = -1;
	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 2, 215, "***********************************");
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
	w = vm->last - 1;// get_winner(vm);
	wattron(stdscr, COLOR_PAIR(w + 1));
	mvwprintw(stdscr, 25 + vm->number_of_bots * 4, 215, "%.37s", vm->bot[w].name);
	wattroff(stdscr, COLOR_PAIR(w + 1));
	mvwprintw(stdscr, 27 + vm->number_of_bots * 4, 199, "Press any key to finish");
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
	// init_pair(5, COLOR_BLACK, COLOR_WHITE); // differs from orig
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
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
	// draw_static_info();
}
