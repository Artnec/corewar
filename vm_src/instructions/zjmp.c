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

int		zjmp(t_list *carry, t_vm *vm)
{
	carry->p = carry->pc;
	iterate(&carry->p, 1);
	if (carry->carry == 1)
		iterate(&carry->pc, (short)get_rdi_val(carry, DIR_CODE, 2, vm) % IDX_MOD);
	else
		iterate(&carry->pc, 3);
	return (0);
}
