/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:13:00 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 20:13:02 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		err_put_nbr(unsigned int nbr)
{
	if (nbr > 9)
		err_put_nbr(nbr / 10);
	nbr = nbr % 10 + 48;
	write(2, &nbr, 1);
}

static int		get_error_line(char *file, int i)
{
	int n;
	int j;

	j = 1;
	n = 0;
	while (n < i)
	{
		if (file[n++] == '\n')
			j++;
	}
	return (j);
}

void			*exit_lexical_error(char *file, int n)
{
	int j;
	int i;

	write(2, "Error at line: ", 15);
	err_put_nbr(get_error_line(file, n));
	write(2, " column: ", 9);
	i = n;
	while (file[i] && file[++i] != '\n')
	{
		if (file[i] == ' ' || file[i] == '\t')
		{
			while (file[i] == ' ' || file[i] == '\t')
				i++;
			file[i] = COMMENT_CHAR;
			if (is_t_reg(file, n) || is_t_dir(file, n) || is_t_ind(file, n))
				n = i;
		}
	}
	j = 1;
	while (--n >= 0 && file[n] != '\n')
		j++;
	err_put_nbr(j);
	write(2, "\n", 1);
	exit(1);
}

static void		print_err_opcode(int i, char *file)
{
	while (i > 0 && file[i - 1] != '\n')
	{
		if (file[i] == LABEL_CHAR && is_label_char(file[i - 1]))
		{
			i++;
			while (file[i] == ' ' || file[i] == '\t')
				i++;
			break ;
		}
		i--;
	}
	while (file[i] == ' ' || file[i] == '\t')
		i++;
	while (file[i] != ' ' && file[i] != '\t' && file[i] != DIRECT_CHAR)
		write(2, &file[i++], 1);
}

void			exit_wrong_parameter(int n, int parameter, int i, t_asm *s)
{
	if (n == 1)
		write(2, "first", 5);
	else if (n == 2)
		write(2, "second", 6);
	else if (n == 3)
		write(2, "thrird", 6);
	write(2, " parameter type of opcode ", 26);
	print_err_opcode(i, s->file);
	write(2, " on line ", 9);
	err_put_nbr(get_error_line(s->file, i));
	write(2, " must be ", 9);
	if (parameter == T_REG)
		write(2, "T_REG\n", 6);
	else if (parameter == T_DIR)
		write(2, "T_DIR\n", 6);
	else if (parameter == T_IND)
		write(2, "T_IND\n", 6);
	else if (parameter == (T_REG | T_DIR))
		write(2, "T_REG or T_DIR\n", 15);
	else if (parameter == (T_REG | T_IND))
		write(2, "T_REG or T_IND\n", 15);
	else if (parameter == (T_DIR | T_IND))
		write(2, "T_DIR or T_IND\n", 15);
	exit(1);
}
