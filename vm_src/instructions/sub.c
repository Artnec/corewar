/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:42 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/31 21:58:44 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sub(t_carry *carry, t_vm *vm)
{
	printf("sub\n");
	carry->pc++;
	if (vm->map[carry->pc++].val != 0x54)
		return (0);
	int n = carry->pc;
	carry->registry[vm->map[n + 2].val] = carry->registry[vm->map[n].val] - 
	carry->registry[vm->map[n].val + 1];
	carry->carry = carry->registry[vm->map[n + 2].val] == 0 ? 1 : 0;
	carry->pc += 3;
	return (0);
}
