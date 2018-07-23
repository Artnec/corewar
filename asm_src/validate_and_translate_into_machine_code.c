/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_translate_into_machine_code.          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 19:34:52 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 19:34:53 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				str_cmp(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == '\0');
}

static void		find_op_label(t_list *opl, t_list *labels, t_asm *s)
{
	int		i;

	while (labels)
	{
		i = 0;
		while (opl->str[i] && labels->str[i] && opl->str[i] == labels->str[i])
			i++;
		if (opl->str[i] == '\0' && labels->str[i] == '\0')
		{
			if (opl->label_size == 2)
				unsigned_short_to_code(labels->n - opl->n, opl->p, s);
			else
				unsigned_int_to_code(labels->n - opl->n, opl->p, s);
			break ;
		}
		labels = labels->next;
	}
	if (labels == NULL)
	{
		write(2, "Error: label ", 13);
		write(2, opl->str, str_len(opl->str));
		write(2, " not found\n", 11);
		exit(1);
	}
}

static void		get_code(int i, t_asm *s)
{
	t_list	*labels_head;
	t_list	*op_labels;

	if (str_len(s->name) > PROG_NAME_LENGTH)
		exit_error("Error: champion name is too long\n");
	if (str_len(s->comment) > COMMENT_LENGTH)
		exit_error("Error: champion comment is too long\n");
	labels_head = get_labels_and_opcodes(i, s);
	op_labels = s->op_labels;
	while (op_labels)
	{
		find_op_label(op_labels, labels_head, s);
		op_labels = op_labels->next;
	}
	if (s->size == 0)
		exit_error("Error: can't create empty champion\n");
	while (labels_head)
	{
		op_labels = labels_head;
		labels_head = labels_head->next;
		free(op_labels->str);
		free(op_labels);
	}
}

static char		*get_name_comment(char *file, int *i, char *name_comment)
{
	int		n;
	int		j;
	char	*str;

	j = 0;
	while (file[*i] == name_comment[j++])
		*i += 1;
	while (file[*i] == ' ' || file[*i] == '\t')
		*i += 1;
	if (file[*i] != '"')
		exit_lexical_error(file, *i);
	n = *i + 1;
	while (file[n] != '"' && file[n])
		n++;
	if (file[n] != '"')
		exit_lexical_error(file, n);
	str = (char *)malloc(n - *i);
	j = 0;
	while (++(*i) < n)
		str[j++] = file[*i];
	str[j] = '\0';
	*i += 1;
	return (str);
}

int				validate_and_translate_into_machine_code(t_asm *s)
{
	int i;

	i = 0;
	while (s->file[i])
	{
		while (s->file[i] == ' ' || s->file[i] == '\t' || s->file[i] == '\n')
			i++;
		if (s->file[i] == COMMENT_CHAR || s->file[i] == COMMENT)
		{
			while (s->file[i] != '\n' && s->file[i])
				i++;
		}
		else if (s->name == NULL && str_cmp(NAME_CMD_STRING, s->file + i))
			s->name = get_name_comment(s->file, &i, NAME_CMD_STRING);
		else if (s->comment == NULL && str_cmp(COMMENT_CMD_STRING, s->file + i))
			s->comment = get_name_comment(s->file, &i, COMMENT_CMD_STRING);
		else
			exit_lexical_error(s->file, i);
		if (s->name && s->comment)
		{
			get_code(i, s);
			return (0);
		}
	}
	return (1);
}
