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

int				str_cmp(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == '\0');
}

int				str_len(char *str)
{
	int l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void			put_nbr(unsigned int nbr)
{
	if (nbr > 9)
		put_nbr(nbr / 10);
	nbr = nbr % 10 + 48;
	write(2, &nbr, 1);
}

void			*exit_lexical_error(char *file, int n)
{
	int j;
	int i;

	j = 1;
	i = -1;
	while (++i < n)
	{
		if (file[i] == '\n')
			j++;
	}
	write(2, "Lexical error at line:", 22);
	put_nbr(j);
	write(2, " column:", 8);
	j = 1;
	while (--i >= 0 && file[i] != '\n')
		j++;
	put_nbr(j);
	write(2, "\n", 1);
	exit(1);
}

char			*get_name_comment(char *file, int *i, char *name_comment)
{
	int		n;
	int		j;
	char	*str;

	j = 0;
	while (file[*i] == name_comment[j++])
		*i += 1;
	while (file[*i] == ' ' || file[*i] == '	')
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
	return (str);
}

void			validate_and_get_name_comment(t_asm *s)
{
	int i;

	i = -1;
	while (s->file[++i])
	{
		while (s->file[i] == '#')
		{
			while (s->file[i] != '\n' && s->file[i] != '\0')
				i++;
			if (s->file[i] != '\0')
				i++;
		}
		while (s->file[i] == ' ' || s->file[i] == '	' || s->file[i] == '\n')
			i++;
		if (s->name == NULL && str_cmp(NAME_CMD_STRING, s->file + i))
			s->name = get_name_comment(s->file, &i, NAME_CMD_STRING);
		else if (s->comment == NULL && str_cmp(COMMENT_CMD_STRING, s->file + i))
			s->comment = get_name_comment(s->file, &i, COMMENT_CMD_STRING);
		else if (s->file[i] != '#')
			exit_lexical_error(s->file, i);
		if (s->name && s->comment)
			return ;
	}
}

void			read_s_file(int fd, t_asm *s)
{
	int		size;

	if (str_len(NAME_CMD_STRING) == 0 || str_len(COMMENT_CMD_STRING) == 0)
	{
		write(2, "Error: empty CMD_STRING\n", 22);
		exit(1);
	}
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	s->file = (char *)malloc(size + 1);
	read(fd, s->file, size);
	s->file[size] = '\0';
	validate_and_get_name_comment(s);
}

char			*get_cor_file_name(char *s_file_name, char *cor)
{
	int		l;
	int		n;
	char	*cor_file_name;

	l = str_len(s_file_name);
	n = l - 1;
	while (n >= 0 && s_file_name[n] != '.')
		n--;
	if (n < 0)
		n = l;
	cor_file_name = (char *)malloc(n + 5);
	l = -1;
	while (++l < n)
		cor_file_name[l] = s_file_name[l];
	l = 0;
	while (cor[l])
		cor_file_name[n++] = cor[l++];
	cor_file_name[n] = '\0';
	return (cor_file_name);
}

void			create_cor_file(char *s_file_name, t_asm *s)
{
	s->cor_file_name = get_cor_file_name(s_file_name, ".cor");
	s->cor_fd = open(s->cor_file_name, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (s->cor_fd == -1)
	{
		write(2, "Error: can't create file\n", 25);
		exit(3);
	}
}

unsigned int	int32_reverse_endian(unsigned int num)
{
	return ((num & 0xff000000) >> 24) | ((num & 0x00ff0000) >> 8)
	| ((num & 0x0000ff00) << 8) | (num << 24);
}

void			write_into_cor_file(t_asm *s)
{
	const char			zero = 0;
	const unsigned int	magic = int32_reverse_endian(COREWAR_EXEC_MAGIC);
	const unsigned int	size = int32_reverse_endian(0xabcde);
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
	// get real size before this.
	write(s->cor_fd, &size, 4);
	i = 0;
	while (s->comment[i])
		write(s->cor_fd, &s->comment[i++], 1);
	while (i++ < COMMENT_LENGTH + 4)
		write(s->cor_fd, &zero, 1);
}

int				main(int argc, char **argv)
{
	t_asm	s;
	int		fd;

	if (argc != 2)
	{
		write(2, "usage: ./asm filename\n", 22);
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		write(2, "Error: can't read source file\n", 30);
		return (2);
	}
	s.name = NULL;
	s.comment = NULL;
	read_s_file(fd, &s);
	create_cor_file(argv[1], &s);
	write_into_cor_file(&s);
	close(fd);
	return (0);
}
