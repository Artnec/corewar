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

void	for_visualization_purpose(t_lst *carry, t_vm *vm, int i, int n)
{
	vm->map[carry->pc - 1].live_id = (vm->bot[i - 1].alive == 1 ? -n : vm->map[carry->pc - 1].live_id);
	if (vm->bot[i - 1].alive == 1 && vm->cycle >= vm->cycle_to_start)
	{
		vm->map[carry->pc - 1].bold = 49;
		vm->map[carry->pc - 1].live = 49;
	}
	else if (vm->bot[i - 1].alive == 1 && vm->cycle >= vm->cycle_to_start - 49)
	{
		vm->map[carry->pc - 1].bold = vm->cycle - vm->cycle_to_start + 50;
		vm->map[carry->pc - 1].live = vm->cycle - vm->cycle_to_start + 50;
	}
}

int		live(t_lst *carry, t_vm *vm)
{
	int i;
	int n;

	vm->lives_in_cycle++;
	carry->alive = 1;
	n = get_uint(vm->map, carry->pc);
	if (vm->bot[carry->id - 1].alive == 1 && -n > vm->number_of_bots && vm->cycle >= vm->cycle_to_start - 49)
	{
		vm->map[carry->pc - 1].live_id = carry->id;
		vm->map[carry->pc - 1].bold = 49 - vm->cycle_to_start - vm->cycle;
		vm->map[carry->pc - 1].live = 49 - vm->cycle_to_start - vm->cycle;
	}
	i = 0;
	while (++i <= vm->number_of_bots)
	{
		if (n == -i)
		{
			vm->bot[i - 1].lives_in_cycle += 1;
			vm->bot[i - 1].last_live = vm->cycle + 1;
			for_visualization_purpose(carry, vm, i, n);
			vm->last = -n;
			break ;
		}
	}
	iterate(&carry->pc, 4);
	return (0);
}
