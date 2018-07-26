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

# include "op.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ncurses.h>


# include <stdio.h>

typedef struct		s_carry
{
	unsigned int	registry[REG_NUMBER];
	int				pc;
	int				id;
	int				carry;
	int				cycles;
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
	int				(*functions[16])(t_carry *carry, struct s_vm *);
	int				cycle;
}					t_vm;

typedef struct		s_op
{
	char			*name;
	int				args_num;
	int				args[3];
	int				opcode;
	int				cycles;
	char			*opcode_description;
	int				codage;
	int				label_size;
}					t_op;

/*
**					op.c
*/
extern t_op			g_op_tab[17];

// int					str_compare(char *a, char *b);
// int					str_num_compare(unsigned char *s, unsigned int num);
// int					mem_compare(void *one, void *two, int n);
void				parse_arguments(int argc, char **argv, t_vm *vm);
void				read_cor_files(t_vm *vm);
void				change_bot_order(int *a, t_vm *vm);
void				exit_error(char *error_message);


void				draw_ncurses(t_vm *vm);
void				start_ncurses(void);


unsigned int		get_uint(t_map *map);
unsigned short		get_usrt(t_map *map);
void				uint_to_map(unsigned int n, int id, t_map *map);
unsigned int		get_rdi_val(t_carry *carry, int t_rdi, int d, t_vm *vm);


int					add(t_carry *carry, t_vm *vm);
int					sub(t_carry *carry, t_vm *vm);
int					ld(t_carry *carry, t_vm *vm);
int					sti(t_carry *carry, t_vm *vm);

#endif
