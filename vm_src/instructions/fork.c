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

int		fork_op(t_list *carry, t_vm *vm)
{
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	fork_carry(carry, vm, (short)get_usrt(vm->map, carry->p) % IDX_MOD);
	iterate(&carry->pc, 3);
	vm->processes++;
	return (0);
}
