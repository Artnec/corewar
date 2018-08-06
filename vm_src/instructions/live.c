/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 20:03:53 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/27 20:03:54 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		set_the_bots_color(t_lst *carry, t_vm *vm, int n)
{
	vm->map[carry->pc - 1].live_id = -n;
	if (vm->cycle >= vm->cycle_to_start)
	{
		vm->map[carry->pc - 1].bold = 49;
		vm->map[carry->pc - 1].live = 49;
	}
	else if (vm->cycle >= vm->cycle_to_start - 49)
	{
		vm->map[carry->pc - 1].bold = vm->cycle - vm->cycle_to_start + 50;
		vm->map[carry->pc - 1].live = vm->cycle - vm->cycle_to_start + 50;
	}
}

int				live(t_lst *carry, t_vm *vm)
{
	int i;
	int n;

	vm->lives_in_cycle++;
	carry->alive = 1;
	n = get_uint(vm->map, carry->pc);
	i = 0;
	while (++i <= vm->number_of_bots)
	{
		if (n == -i)
		{
			vm->bot[i - 1].lives_in_cycle += 1;
			vm->bot[i - 1].last_live = vm->cycle + 1;
			set_the_bots_color(carry, vm, n);
			vm->last = -n;
			break ;
		}
	}
	iterate(&carry->pc, 4);
	return (0);
}
