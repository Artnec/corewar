/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 12:48:45 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 12:48:47 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		fork_op(t_lst *carry, t_vm *vm)
{
	fork_carry(carry, vm, get_short(vm->map, carry->pc) % IDX_MOD);
	iterate(&carry->pc, 2);
	vm->processes++;
	sound_stuff(vm, 3);
	return (0);
}
