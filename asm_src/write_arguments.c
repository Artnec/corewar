/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 21:39:05 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/23 21:39:06 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		putnum_fd(int fd, unsigned int num)
{
	if (num > 9)
		putnum_fd(fd, num / 10);
	num = num % 10 + '0';
	write(fd, &num, 1);
}

static int		write_arg(int fd, unsigned char *code, int t, int n)
{
	if (t == T_REG)
	{
		write(fd, "r", 1);
		if (*code > 99)
			exit_error("error: register number is too large\n");
		putnum_fd(fd, *code);
		return (1);
	}
	else if (t == T_DIR)
	{
		write(fd, "%", 1);
		if (n == 1)
			putnum_fd(fd, code[1] | *code << 8);
		else if (n == 0)
			putnum_fd(fd, code[3] | code[2] << 8 | code[1] << 16 | *code << 24);
		return (n == 1 ? 2 : 4);
	}
	if (*code > 9)
		putnum_fd(fd, 0xffff - (code[1] | *code << 8));
	else
		putnum_fd(fd, code[1] | *code << 8);
	return (2);
}

static int		get_arg2(int t, int c)
{
	if (t == (T_REG | T_IND))
	{
		if (c == REG_CODE)
			return (T_REG);
		else if (c == IND_CODE)
			return (T_IND);
		exit_error("error: wrong argument\n");
	}
	else if (t == (T_DIR | T_IND))
	{
		if (c == DIR_CODE)
			return (T_DIR);
		else if (c == IND_CODE)
			return (T_IND);
		exit_error("error: wrong argument\n");
	}
	exit_error("error: wrong argument\n");
	return (0);
}

static int		get_arg(int t, int c)
{
	if ((t == T_REG || t == T_DIR || t == T_IND) && c == 0)
		return (t);
	if ((t == T_REG && c == REG_CODE) || (t == T_DIR && c == DIR_CODE) ||
		(t == T_IND && c == IND_CODE))
		return (t);
	else if (t == (T_REG | T_DIR | T_IND))
	{
		if (c == REG_CODE)
			return (T_REG);
		else if (c == DIR_CODE)
			return (T_DIR);
		else if (c == IND_CODE)
			return (T_IND);
		exit_error("error: wrong argument\n");
	}
	else if (t == (T_REG | T_DIR))
	{
		if (c == REG_CODE)
			return (T_REG);
		else if (c == DIR_CODE)
			return (T_DIR);
		exit_error("error: wrong argument\n");
	}
	return (get_arg2(t, c));
}

int				write_arguments(int fd, int i, t_rev *rev)
{
	int		n;
	int		j;
	int		arg;
	int		t_rdi;

	if ((n = rev->code[i++] - 1) > 15)
		exit_error("error: wrong opcode\n");
	arg = g_op_tab[n].codage == 0 ? 0 : rev->code[i++];
	write(fd, g_op_tab[n].name, str_len(g_op_tab[n].name));
	str_len(g_op_tab[n].name) > 3 ? write(fd, "\t", 1) : write(fd, "\t\t", 2);
	j = 0;
	while (++j <= g_op_tab[n].args_num)
	{
		t_rdi = get_arg(g_op_tab[n].args[j - 1], arg >> (8 - j * 2) & 0x3);
		i += write_arg(fd, rev->code + i, t_rdi, g_op_tab[n].label_size);
		j == g_op_tab[n].args_num ? write(fd, "\n", 1) : write(fd, ", ", 2);
	}
	return (i);
}
