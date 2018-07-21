/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode_to_machine_code.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 21:05:43 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 21:05:44 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		skip_argument_and_separator(char *file, int *i)
{
	while (file[*i] != '\n' && file[*i] != SEPARATOR_CHAR)
		*i += 1;
	if (file[*i] != SEPARATOR_CHAR)
		exit_lexical_error(file, *i);
	*i += 1;
	while (file[*i] == ' ' || file[*i] == '\t')
		*i += 1;
}

static int		get_argument3(int n, int argument, int i, t_asm *s)
{
	if (argument == (T_DIR | T_IND))
	{
		if (is_t_dir(s->file, i))
			return (get_direct_value(i + 1, s));
		else if (is_t_ind(s->file, i))
			return (get_indirect_value(i, s));
		else if (is_t_reg(s->file, i))
			exit_wrong_parameter(n, T_DIR | T_IND, i, s);
	}
	else if (argument == (T_REG | T_DIR | T_IND))
	{
		if (is_t_reg(s->file, i))
			return (get_register_value(i + 1, s));
		else if (is_t_dir(s->file, i))
			return (get_direct_value(i + 1, s));
		else if (is_t_ind(s->file, i))
			return (get_indirect_value(i, s));
	}
	exit_lexical_error(s->file, i);
	return (0);
}

static int		get_argument2(int n, int argument, int i, t_asm *s)
{
	if (argument == (T_REG | T_DIR))
	{
		if (is_t_reg(s->file, i))
			return (get_register_value(i + 1, s));
		else if (is_t_dir(s->file, i))
			return (get_direct_value(i + 1, s));
		else if (is_t_ind(s->file, i))
			exit_wrong_parameter(n, T_REG | T_DIR, i, s);
	}
	else if (argument == (T_REG | T_IND))
	{
		if (is_t_reg(s->file, i))
			return (get_register_value(i + 1, s));
		else if (is_t_ind(s->file, i))
			return (get_indirect_value(i, s));
		else if (is_t_dir(s->file, i))
			exit_wrong_parameter(n, T_REG | T_IND, i, s);
	}
	return (get_argument3(n, argument, i, s));
}

static int		get_argument(int n, int argument, int i, t_asm *s)
{
	if (argument == T_REG)
	{
		if (is_t_reg(s->file, i))
			return (get_register_value(i + 1, s));
		else if (is_t_dir(s->file, i) || is_t_ind(s->file, i))
			exit_wrong_parameter(n, T_REG, i, s);
	}
	else if (argument == T_DIR)
	{
		if (is_t_dir(s->file, i))
			return (get_direct_value(i + 1, s));
		else if (is_t_reg(s->file, i) || is_t_ind(s->file, i))
			exit_wrong_parameter(n, T_DIR, i, s);
	}
	else if (argument == T_IND)
	{
		if (is_t_ind(s->file, i))
			return (get_indirect_value(i, s));
		else if (is_t_reg(s->file, i) || is_t_dir(s->file, i))
			exit_wrong_parameter(n, T_IND, i, s);
	}
	return (get_argument2(n, argument, i, s));
}

void			opcode_to_machine_code(int i, int opcode, t_asm *s)
{
	int n;
	int j;

	if (s->size > CORE_CHAMP_MAX_SIZE - 11)
		exit_error("Error: champion size is to large\n");
	s->code[s->size++] = opcode--;
	s->arg_flag = s->size;
	if (g_op_tab[opcode].codage == 1)
		s->size++;
	while (s->file[i] != ' ' && s->file[i] != '\t' && s->file[i] != DIRECT_CHAR)
		i++;
	while (s->file[i] == ' ' || s->file[i] == '\t')
		i++;
	j = 0;
	s->code[s->arg_flag] = 0;
	while (++j <= g_op_tab[opcode].args_num)
	{
		s->t_dir_size = (g_op_tab[opcode].label_size == 1 ? 2 : 4);
		n = get_argument(j, g_op_tab[opcode].args[j - 1], i, s) << (8 - j * 2);
		if (g_op_tab[opcode].codage == 1)
			s->code[s->arg_flag] += n;
		if (j < g_op_tab[opcode].args_num)
			skip_argument_and_separator(s->file, &i);
	}
	check_seperator_after_argument(s->file, i);
}
