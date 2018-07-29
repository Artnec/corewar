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

int		lfork(t_list *carry, t_vm *vm)
{
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	fork_carry(carry, vm, (short)get_usrt(vm->map, carry->p));
	iterate(&carry->pc, 3);
	vm->processes++;
	return (0);
}

