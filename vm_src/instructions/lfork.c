/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 14:55:42 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 14:55:44 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lfork(t_lst *carry, t_vm *vm)
{
	fork_carry(carry, vm, get_short(vm->map, carry->pc));
	iterate(&carry->pc, 2);
	vm->processes++;
	sound_stuff(vm, 3);
	if (vm->v == 1 && vm->cycle >= vm->cycle_to_start)
		system("afplay corsound/oh_my.mp3&");
	return (0);
}
