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

int		live(t_lst *carry, t_vm *vm)
{
	int i;
	int n;

	vm->lives_in_cycle++;
	carry->alive = 1;
	n = get_uint(vm->map, carry->pc);
	vm->map[carry->pc - 1].live_id = carry->id;
	i = 0;
	while (++i <= vm->number_of_bots)
	{
		if (n == -i)
		{
			vm->bot[i - 1].lives_in_cycle += 1;
			vm->bot[i - 1].last_live = vm->cycle + 1;
			vm->map[carry->pc - 1].live_id = -n;
			vm->last = -n;
			break ;
		}
	}
	vm->map[carry->pc - 1].bold = 49;
	vm->map[carry->pc - 1].live = 49;
	iterate(&carry->pc, 4);
	return (0);
}
