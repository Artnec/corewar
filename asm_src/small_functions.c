/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 21:01:17 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 21:01:18 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		str_len(char *str)
{
	int l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void	exit_error(char *error_message)
{
	write(2, error_message, str_len(error_message));
	exit(1);
}

int		is_label_char(char c)
{
	const char	label_chars[] = LABEL_CHARS;
	int			i;

	i = 0;
	while (label_chars[i] != '\0')
	{
		if (label_chars[i++] == c)
			return (1);
	}
	return (0);
}

int		unsigned_int_to_code(unsigned int num, int n, t_asm *s)
{
	s->code[n] = num >> 24 & 0xff;
	s->code[n + 1] = num >> 16 & 0xff;
	s->code[n + 2] = num >> 8 & 0xff;
	s->code[n + 3] = num & 0xff;
	return (4);
}

int		unsigned_short_to_code(unsigned short num, int n, t_asm *s)
{
	s->code[n] = num >> 8;
	s->code[n + 1] = num & 0xff;
	return (2);
}
