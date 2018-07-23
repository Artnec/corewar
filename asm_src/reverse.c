/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:23:48 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/23 15:23:50 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		create_s_file(char *file)
{
	int i;
	int fd;

	i = str_len(file) - 2;
	file[i] = '\0';
	file[i - 1] = 's';
	if ((fd = open(file, O_CREAT | O_EXCL | O_WRONLY, 0600)) == -1)
		exit_error("Error: can't create file\n");
	return (fd);
}

static void		write_into_s_file(int fd, t_rev *rev)
{
	unsigned int	i;

	write(fd, ".name	\"", 7);
	write(fd, rev->name, str_len(rev->name));
	write(fd, "\"\n", 2);
	write(fd, ".comment	\"", 10);
	write(fd, rev->comment, str_len(rev->comment));
	write(fd, "\"\n\n", 3);
	i = 0;
	while (i < rev->size)
		i = write_arguments(fd, i, rev);
	write(1, "Writing output program to .s file\n", 34);
}

static int		str_num_compare(unsigned char *s, unsigned int num)
{
	return ((unsigned int)(s[3] | s[2] << 8 | s[1] << 16 | s[0] << 24) == num);
}

static void		validate_and_get_code(int fd, t_rev *rev)
{
	unsigned char	a[4];

	rev->size = 0;
	if (read(fd, a, 4) != 4 || str_num_compare(a, COREWAR_EXEC_MAGIC) == 0)
		exit_error("invalid magic number\n");
	if (read(fd, rev->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		exit_error("not enough info in .cor file\n");
	if (read(fd, a, 4) != 4 || str_num_compare(a, 0) == 0)
		exit_error("four zeroed bytes after bot name not found\n");
	if (read(fd, a, 4) != 4)
		exit_error("not enough info in .cor file\n");
	if ((rev->size = a[3] | a[2] << 8 | a[1] << 16 | a[0] << 24) > 2048)
		exit_error("size of the bot is too large\n");
	if (read(fd, rev->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		exit_error("not enough info in .cor file\n");
	if (read(fd, a, 4) != 4 || str_num_compare(a, 0) == 0)
		exit_error("four zeroed bytes after bot comment not found\n");
	if (read(fd, rev->code, rev->size) != rev->size)
		exit_error("not enough info in .cor file\n");
	if (read(fd, a, 1) != 0)
		exit_error("excess data at the end of the file\n");
	if (close(fd) == -1)
		exit_error("error while closing file descriptor\n");
}

void			reverse(char *file)
{
	int				fd;
	int				i;
	t_rev			rev;

	i = str_len(file) - 1;
	if (i < 4 || file[i - 3] != '.' || file[i - 2] != 'c' ||
		file[i - 1] != 'o' || file[i] != 'r')
	{
		write(2, "error file should have .cor extension\n", 38);
		return ;
	}
	if ((fd = open(file, O_RDONLY)) == -1 || (read(fd, &i, 0)) == -1)
	{
		write(2, "error file does not exist\n", 26);
		return ;
	}
	validate_and_get_code(fd, &rev);
	fd = create_s_file(file);
	write_into_s_file(fd, &rev);
}
