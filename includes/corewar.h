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
# include <time.h>

# define REG_CHECK(x)			(x < 1 || x > REG_NUMBER)
# define IS_VALID_OPCODE(x)		(x > 0 && x < 17)

typedef struct		s_lst
{
	int				registry[REG_NUMBER];
	int				pc;
	int				op;
	int				opcode;
	int				codage;
	int				id;
	int				carry;
	int				cycles;
	int				alive;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_map
{
	unsigned char	val;
	int				id;
	int				bold;
	int				live;
	int				live_id;
}					t_map;

typedef struct		s_bot
{
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	bot[CHAMP_MAX_SIZE];
	long			size;
	int				lives_in_cycle;
	int				last_live;
}					t_bot;

typedef struct		s_vm
{
	t_lst			*carry_list_head;
	int				v;
	int				a_flag;
	int				dump;
	int				number_of_bots;
	char			*bot_filenames[4];
	t_bot			bot[MAX_PLAYERS];
	t_map			map[MEM_SIZE];
	int				(*functions[16])(t_lst *carry, struct s_vm *);
	int				cycle;
	int				cycle_to_start;
	unsigned int	cycle_alive;
	unsigned int	cycle_to_die;
	int				checks_count;
	int				processes;
	int				lives_in_cycle;
	int				fps;
	int				last;
	int				s;
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

int					ft_printf(const char *fmt, ...);

void				parse_arguments(int argc, char **argv, t_vm *vm, int i);
int					str_compare(char *a, char *b);
void				flag_searcher(t_vm *vm, char **argv, int *i);
void				read_cor_files(t_vm *vm);
void				change_bot_order(int *a, t_vm *vm);
int					check_codage_and_regs(t_lst *carry, t_vm *vm);
void				corewar(t_vm *vm);
void				run_cycle(t_vm *vm);
void				exit_error(char *error_message);
void				show_usage(void);
void				player_introduction(t_vm *vm);
void				dump_memory(t_vm *vm);

void				draw_ncurses(t_vm *vm);
void				start_ncurses(void);
void				end_ncurses(t_vm *vm);
void				pause_ncurses(t_vm *vm);
void				key_control(t_vm *vm);
void				sound_stuff(t_vm *vm, int i);

unsigned int		get_uint(t_map *map, int n);
short				get_short(t_map *map, int n);
void				uint_to_map(unsigned int n, int id, t_vm *vm, int i);
int					get_rdi_val(t_lst *carry, int t_rdi, int d, t_vm *vm);
int					iterate(int *pc, int n);
void				fork_carry(t_lst *orig_carry, t_vm *vm, int pos);

/*
**					vm_src/instructions
*/
int					live(t_lst *carry, t_vm *vm);
int					ld(t_lst *carry, t_vm *vm);
int					st(t_lst *carry, t_vm *vm);
int					add(t_lst *carry, t_vm *vm);
int					sub(t_lst *carry, t_vm *vm);
int					and(t_lst *carry, t_vm *vm);
int					or(t_lst *carry, t_vm *vm);
int					xor(t_lst *carry, t_vm *vm);
int					zjmp(t_lst *carry, t_vm *vm);
int					ldi(t_lst *carry, t_vm *vm);
int					sti(t_lst *carry, t_vm *vm);
int					fork_op(t_lst *carry, t_vm *vm);
int					lld(t_lst *carry, t_vm *vm);
int					lldi(t_lst *carry, t_vm *vm);
int					lfork(t_lst *carry, t_vm *vm);
int					aff(t_lst *carry, t_vm *vm);

#endif
