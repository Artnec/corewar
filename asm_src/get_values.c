/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:26:10 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 20:26:12 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static long		ft_atoi(char *str, int i)
{
	int		num;
	int		s;
	int		n;

	s = (str[i] == '-' && ++i) ? -1 : 1;
	while (str[i] == '0')
		i++;
	num = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - 48;
		n++;
	}
	if (n >= 20)
		return (s == -1 ? 0 : 9223372036854775807);
	return (num * s);
}

static t_list	*get_op_label(int i, int label_size, t_asm *s)
{
	int		n;
	int		t;
	t_list	*op_label;

	n = 0;
	while (is_label_char(s->file[i]) == 1)
	{
		i++;
		n++;
	}
	if (n == 0)
		exit_lexical_error(s->file, i);
	op_label = (t_list *)malloc(sizeof(t_list));
	op_label->next = s->op_labels;
	op_label->n = s->arg_flag - 1;
	op_label->p = s->size;
	op_label->label_size = label_size;
	op_label->str = (char *)malloc(n + 1);
	op_label->str[n] = '\0';
	i -= n;
	t = -1;
	while (++t < n)
		op_label->str[t] = s->file[i++];
	return (op_label);
}

int				get_register_value(int i, t_asm *s)
{
	s->code[s->size] = s->file[i] - 48;
	if (s->file[i + 1] >= '0' && s->file[i + 1] <= '9')
		s->code[s->size] = s->code[s->size] * 10 + s->file[i + 1] - 48;
	s->size += 1;
	return (REG_CODE);
}

int				get_direct_value(int i, t_asm *s)
{
	if (s->file[i] == LABEL_CHAR && ++i)
	{
		s->op_labels = get_op_label(i, s->t_dir_size, s);
		s->size += s->t_dir_size;
	}
	else if (s->t_dir_size == 4)
		s->size += unsigned_int_to_code(ft_atoi(s->file, i), s->size, s);
	else if (s->t_dir_size == 2)
		s->size += unsigned_short_to_code(ft_atoi(s->file, i), s->size, s);
	return (DIR_CODE);
}

int				get_indirect_value(int i, t_asm *s)
{
	if (s->file[i] == LABEL_CHAR && ++i)
	{
		s->op_labels = get_op_label(i, 2, s);
		s->size += 2;
	}
	else
		s->size += unsigned_short_to_code(ft_atoi(s->file, i), s->size, s);
	return (IND_CODE);
}
