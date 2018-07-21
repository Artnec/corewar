/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reg_dir_ind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:50:02 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 20:50:03 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_comment_endline_separator(char c)
{
	return (c == SEPARATOR_CHAR || c == '\n'
		|| c == COMMENT_CHAR || c == COMMENT);
}

int			is_t_reg(char *file, int i)
{
	if (file[i++] == 'r')
	{
		if (file[i] >= '0' && file[i] <= '9' && ++i)
		{
			if (file[i] >= '0' && file[i] <= '9' && ++i)
			{
				while (file[i] == ' ' || file[i] == '\t')
					i++;
				return (is_comment_endline_separator(file[i]));
			}
			while (file[i] == ' ' || file[i] == '\t')
				i++;
			return (is_comment_endline_separator(file[i]));
		}
	}
	return (0);
}

int			is_t_dir(char *file, int i)
{
	if (file[i++] == DIRECT_CHAR)
	{
		if ((file[i] >= '0' && file[i] <= '9') || file[i] == '-')
		{
			if (file[i] == '-')
				i++;
			while (file[i] >= '0' && file[i] <= '9')
				i++;
			while (file[i] == ' ' || file[i] == '\t')
				i++;
			return (is_comment_endline_separator(file[i]));
		}
		else if (file[i] == LABEL_CHAR && ++i)
		{
			while (is_label_char(file[i]))
				i++;
			while (file[i] == ' ' || file[i] == '\t')
				i++;
			return (is_comment_endline_separator(file[i]));
		}
		return (0);
	}
	return (0);
}

int			is_t_ind(char *file, int i)
{
	if ((file[i] >= '0' && file[i] <= '9') || file[i] == '-')
	{
		if (file[i] == '-')
			i++;
		while (file[i] >= '0' && file[i] <= '9')
			i++;
		while (file[i] == ' ' || file[i] == '\t')
			i++;
		return (is_comment_endline_separator(file[i]));
	}
	else if (file[i] == LABEL_CHAR && ++i)
	{
		while (is_label_char(file[i]))
			i++;
		while (file[i] == ' ' || file[i] == '\t')
			i++;
		return (is_comment_endline_separator(file[i]));
	}
	return (0);
}
