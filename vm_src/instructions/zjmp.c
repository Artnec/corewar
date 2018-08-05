/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 12:13:49 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/29 12:13:50 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		zjmp(t_lst *carry, t_vm *vm)
{
	if (carry->carry == 1)
	{
		carry->pc =
			iterate(&carry->op, get_short(vm->map, carry->pc) % IDX_MOD);
	}
	else
		iterate(&carry->pc, 2);
	return (0);
}
