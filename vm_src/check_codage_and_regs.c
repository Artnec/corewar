/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_codage_and_regs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:54:53 by anesteru          #+#    #+#             */
/*   Updated: 2018/08/04 19:54:53 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		check_dir_ind(int c, int args, int *p, int op)
{
	if (c == DIR_CODE)
	{
		iterate(p, g_op_tab[op].label_size == 1 ? 2 : 4);
		if ((args & T_DIR) == 0)
			return (1);
	}
	else if (c == IND_CODE)
	{
		iterate(p, 2);
		if ((args & T_IND) == 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

static int		check_opcode_with_codage(int op, int p, t_lst *carry, t_vm *vm)
{
	int i;
	int error;
	int c;

	error = 0;
	i = -1;
	while (++i < g_op_tab[op].args_num)
	{
		c = (carry->codage >> (4 - i * 2)) & 3;
		if (c == REG_CODE)
		{
			if (!(g_op_tab[op].args[i] & T_REG) || REG_CHECK(vm->map[p].val))
				error = 1;
			iterate(&p, 1);
		}
		else if (check_dir_ind(c, g_op_tab[op].args[i], &p, op))
			error = 1;
	}
	if (error == 1)
		carry->pc = p;
	return (error);
}

int				check_codage_and_regs(t_lst *carry, t_vm *vm)
{
	int error;
	int op;

	error = 0;
	carry->op = carry->pc;
	op = carry->opcode;
	iterate(&carry->pc, 1);
	if (g_op_tab[op].codage == 1)
	{
		carry->codage = vm->map[carry->pc].val >> 2;
		iterate(&carry->pc, 1);
		error = check_opcode_with_codage(op, carry->pc, carry, vm);
	}
	else if (g_op_tab[op].args[0] == T_REG &&
		(error = REG_CHECK(vm->map[carry->pc].val)))
		iterate(&carry->pc, 1);
	return (error == 0);
}
