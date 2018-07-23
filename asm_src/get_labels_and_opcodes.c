/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels_and_opcodes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 19:59:58 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 19:59:59 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		is_opcode(const char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == '\0' && (*b == ' ' || *b == '\t' || *b == DIRECT_CHAR));
}

static int		get_opcode(char *file)
{
	int			n;

	n = 0;
	while (g_op_tab[n].name != NULL)
	{
		if (is_opcode(g_op_tab[n++].name, file))
			return (n);
	}
	return (0);
}

static t_list	*get_label(char *file, int *i, int cur_size, t_list *head)
{
	int		n;
	t_list	*label;

	n = 0;
	while (is_label_char(file[*i]) == 1)
	{
		*i += 1;
		n++;
	}
	if (file[*i] != LABEL_CHAR || (n == 0 && (file[*i] = '.')))
		exit_lexical_error(file, *i - n);
	label = (t_list *)malloc(sizeof(t_list));
	label->next = head;
	label->str = (char *)malloc(n + 1);
	label->str[n] = '\0';
	*i -= n;
	n = 0;
	while (file[*i] != LABEL_CHAR)
		label->str[n++] = file[(*i)++];
	label->n = cur_size;
	*i += 1;
	return (label);
}

t_list			*get_labels_and_opcodes(int i, t_asm *s)
{
	t_list	*labels;
	int		op;

	labels = NULL;
	while (s->file[i] != '\0')
	{
		while (s->file[i] == ' ' || s->file[i] == '\t' || s->file[i] == '\n')
			i++;
		if (s->file[i] == '\0')
			break ;
		if (s->file[i] == COMMENT_CHAR || s->file[i] == COMMENT)
		{
			while (s->file[i] != '\n')
				i++;
		}
		else if ((op = get_opcode(s->file + i)) == 0)
			labels = get_label(s->file, &i, s->size, labels);
		else
		{
			opcode_to_machine_code(i, op, s);
			while (s->file[i] != '\n' && s->file[i] != '\0')
				i++;
		}
	}
	return (labels);
}
