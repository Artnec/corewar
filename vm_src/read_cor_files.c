/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 21:35:29 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/12 21:35:31 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		str_num_compare(unsigned char *s, unsigned int num)
{
	return ((unsigned int)(s[3] | s[2] << 8 | s[1] << 16 | s[0] << 24) == num);
}

static void		check_the_bot(t_vm *vm, int fd, int i)
{
	unsigned char	a[4];

	if ((fd = open(vm->bot_filenames[i], O_RDONLY)) == -1)
		exit_error("can't open file\n");
	if (read(fd, a, 4) != 4 || str_num_compare(a, COREWAR_EXEC_MAGIC) == 0)
		exit_error("invalid magic number\n");
	if (read(fd, vm->bot[i].name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		exit_error("not enough info in .cor file\n");
	if (read(fd, a, 4) != 4 || str_num_compare(a, 0) == 0)
		exit_error("four zeroed bytes after bot name not found\n");
	if (read(fd, a, 4) != 4)
		exit_error("not enough info in .cor file\n");
	if ((vm->bot[i].size = a[3] | a[2] << 8) > CHAMP_MAX_SIZE ||
		vm->bot[i].size == 0 || a[1] > 0 || a[0] > 0)
		exit_error("size of the bot is invalid\n");
	if (read(fd, vm->bot[i].comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		exit_error("not enough info in .cor file\n");
	if (read(fd, a, 4) != 4 || str_num_compare(a, 0) == 0)
		exit_error("four zeroed bytes after bot comment not found\n");
	if (read(fd, vm->bot[i].bot, vm->bot[i].size) != vm->bot[i].size)
		exit_error("not enough info in .cor file\n");
	if (read(fd, a, 1) != 0)
		exit_error("excess data at the end of the file\n");
	if (close(fd) == -1)
		exit_error("while closing file descriptor\n");
}

void			read_cor_files(t_vm *vm)
{
	int				i;

	i = -1;
	while (++i < vm->number_of_bots)
		check_the_bot(vm, -1, i);
}
