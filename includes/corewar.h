/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:52:22 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/22 17:52:24 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ncurses.h>


# include <stdio.h>

# define MAX_PLAYERS		4
# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define MEM_SIZE			(4*1024)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define REG_NUMBER			16
# define REG_SIZE			4
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct		s_carry
{
	unsigned int	registry[REG_NUMBER];
	int				pc;
	int				carry;
	int				cycle;
	int				alive;
}					t_carry;

typedef struct		s_list
{
	t_carry			*carry;
	struct s_list	*next;
}					t_list;

typedef struct		s_map
{
	unsigned char	val;
	int				id;
}					t_map;

typedef struct		s_bot
{
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	bot[CHAMP_MAX_SIZE];
	long			size;
}					t_bot;

typedef struct		s_vm
{
	t_list			*carry_list;
	t_list			*carry_list_head;
	int				v;
	int				dump;
	int				number_of_bots;
	char			*bot_filenames[4];
	t_bot			bot[MAX_PLAYERS];
	t_map			map[MEM_SIZE];
	int				(*function[16])(struct s_vm *);
	int				cycle;
	int				end;
}					t_vm;

// int					str_compare(char *a, char *b);
int					str_num_compare(unsigned char *s, unsigned int num);
// int					mem_compare(void *one, void *two, int n);
void				parse_arguments(int argc, char **argv, t_vm *vm);
void				change_bot_order(int *a, t_vm *vm);
void				exit_error(char *error_message);


void				draw_ncurses(t_vm *vm);
void				start_ncurses(void);


int					add(t_vm *vm);
int					sub(t_vm *vm);

#endif
