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
	fork_carry(carry, vm, get_short(vm->map, carry->pc));
	iterate(&carry->pc, 2);
	vm->processes++;
	return (0);
}
