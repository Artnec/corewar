/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 18:00:01 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/22 18:00:02 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>

# define COMMENT					';'
# define CORE_CHAMP_MAX_SIZE		2048

typedef struct		s_list
{
	char			*str;
	int				n;
	int				p;
	int				label_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_asm
{
	char			*file;
	char			*name;
	char			*comment;
	char			*cor_file_name;
	unsigned char	code[CORE_CHAMP_MAX_SIZE];
	int				size;
	int				arg_flag;
	int				t_dir_size;
	int				cor_fd;
	t_list			*op_labels;
}					t_asm;

typedef struct		s_rev
{
	unsigned char	*buf;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	code[CORE_CHAMP_MAX_SIZE];
	unsigned int	size;
}					t_rev;

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

/*
**					main.c
*/
void				read_s_file(char *file_name, t_asm *s);
void				create_cor_file(char *s_file_name, t_asm *s);
void				write_into_cor_file(t_asm *s);

/*
**					validate_and_translate_into_machine_code.c
*/
int					validate_and_translate_into_machine_code(t_asm *s);
int					str_cmp(char *a, char *b);

/*
**					get_labels_and_opcodes.c
*/
t_list				*get_labels_and_opcodes(int i, t_asm *s);

/*
**					opcode_to_machine_code.c
*/
void				opcode_to_machine_code(int i, int opcode, t_asm *s);

/*
**					get_values.c
*/
int					get_register_value(int i, t_asm *s);
int					get_direct_value(int i, t_asm *s);
int					get_indirect_value(int i, t_asm *s);

/*
**					is_reg_dir_ind.c
*/
int					is_t_reg(char *file, int i);
int					is_t_dir(char *file, int i);
int					is_t_ind(char *file, int i);

/*
**					check_seperator_after_argument.c
*/
void				check_seperator_after_argument(char *file, int i);

/*
**					small_functions.c
*/
int					str_len(char *str);
void				exit_error(char *error_message);
int					is_label_char(char c);
int					unsigned_int_to_code(unsigned int num, int n, t_asm *s);
int					unsigned_short_to_code(unsigned short num, int n, t_asm *s);

/*
**					translate_all_files_in_directory.c
*/
void				initiate_structure(t_asm *s);
void				free_all(t_asm *s);
void				translate_all_files_in_directory(char *dir_name, t_asm *s);

/*
**					reverse.c
*/
void				reverse(char *file);

/*
**					write_arguments.c
*/
int					write_arguments(int fd, int i, t_rev *rev);

/*
**					error.c
*/
void				exit_wrong_parameter(int n, int parameter, int i, t_asm *s);
void				*exit_lexical_error(char *file, int n);

#endif
