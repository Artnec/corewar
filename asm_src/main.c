/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:50:15 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/22 17:50:19 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			read_s_file(int fd, t_asm *s)
{
	int		size;

	if (str_len(NAME_CMD_STRING) == 0 || str_len(COMMENT_CMD_STRING) == 0)
		exit_error("Error: empty CMD_STRING\n");
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	s->file = (char *)malloc(size + 1);
	read(fd, s->file, size);
	s->file[size] = '\0';
}

static void			create_cor_file(char *s_file_name, t_asm *s)
{
	const char	cor[] = ".cor";
	int			l;
	int			n;

	l = str_len(s_file_name);
	n = l - 1;
	while (n >= 0 && s_file_name[n] != '.')
		n--;
	if (n < 0)
		n = l;
	s->cor_file_name = (char *)malloc(n + 5);
	l = -1;
	while (++l < n)
		s->cor_file_name[l] = s_file_name[l];
	l = 0;
	while (cor[l])
		s->cor_file_name[n++] = cor[l++];
	s->cor_file_name[n] = '\0';
	s->cor_fd = open(s->cor_file_name, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (s->cor_fd == -1)
		exit_error("Error: can't create file\n");
}

static unsigned int	int32_reverse_endian(unsigned int num)
{
	return ((num & 0xff000000) >> 24) | ((num & 0x00ff0000) >> 8)
	| ((num & 0x0000ff00) << 8) | (num << 24);
}

static void			write_into_cor_file(t_asm *s)
{
	const unsigned char	zero = 0;
	const unsigned int	magic = int32_reverse_endian(COREWAR_EXEC_MAGIC);
	const unsigned int	size = int32_reverse_endian(s->size);
	int					i;

	write(1, "Writing output program to ", 26);
	write(1, s->cor_file_name, str_len(s->cor_file_name));
	write(1, "\n", 1);
	write(s->cor_fd, &magic, 4);
	i = 0;
	while (s->name[i])
		write(s->cor_fd, &s->name[i++], 1);
	while (i++ < PROG_NAME_LENGTH + 4)
		write(s->cor_fd, &zero, 1);
	write(s->cor_fd, &size, 4);
	i = 0;
	while (s->comment[i])
		write(s->cor_fd, &s->comment[i++], 1);
	while (i++ < COMMENT_LENGTH + 4)
		write(s->cor_fd, &zero, 1);
	i = 0;
	while (i < s->size)
		write(s->cor_fd, &s->code[i++], 1);
}

int					main(int argc, char **argv)
{
	t_asm	s;
	int		fd;

	if (argc != 2)
		exit_error("usage: ./asm filename\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit_error("Error: can't read source file\n");
	s.name = NULL;
	s.comment = NULL;
	s.size = 0;
	read_s_file(fd, &s);
	validate_and_translate_into_machine_code(&s);
	create_cor_file(argv[1], &s);
	write_into_cor_file(&s);
	close(fd);
	return (0);
}
