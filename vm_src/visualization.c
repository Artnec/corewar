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
	int		n;
	int 	i;
	int 	j;

	tmp = vm->carry_list_head;
	while (tmp)
	{
		wattron(stdscr, COLOR_PAIR(vm->map[tmp->carry->pc].id + 4));
		n = vm->map[tmp->carry->pc].val;
		i = tmp->carry->pc / 64 + 2;
		j = tmp->carry->pc % 64 * 3 + 3;
		mvwprintw(stdscr, i, j, "%c", n / 16 + (n / 16 > 9 ? 87 : 48));
		mvwprintw(stdscr, i, j + 1, "%c", n % 16 + (n % 16 > 9 ? 87 : 48));
		wattroff(stdscr, COLOR_PAIR(vm->map[tmp->carry->pc].id + 4));
		tmp = tmp->next;
	}
}

void			draw_ncurses(t_vm *vm)
{
	int		i;
	int		n;
	int		j;
	char	str[3];

	str[2] = '\0';
	j = 0;
	n = 1;
	while (++n < 66)
	{
		i = 3;
		while (i < 195)
		{
			wattron(stdscr, COLOR_PAIR(vm->map[j].id));
			str[0] = vm->map[j].val / 16 + (vm->map[j].val / 16 > 9 ? 87 : 48);
			str[1] = vm->map[j].val % 16 + (vm->map[j].val % 16 > 9 ? 87 : 48);
			mvwprintw(stdscr, n, i, "%s", str);
			wattroff(stdscr, COLOR_PAIR(vm->map[j++].id));
			i += 3;
		}
	}
	draw_carrys(vm);
	wrefresh(stdscr);
	sleep(30);
}

static void		draw_border(void)
{
	int n;

	n = -1;
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
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	draw_border();
}
