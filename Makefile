# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anesteru <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 16:47:46 by anesteru          #+#    #+#              #
#    Updated: 2018/05/22 16:47:48 by anesteru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM				=	corewar
ASM				=	asm
CMP				=	cmp

VM_SRC			=	main.c		change_bot_order.c	parse_arguments.c \
					read_cor_files.c	op.c run_cycle.c \
					check_codage_and_regs.c	visualization_draw_ncurses.c \
					visualization_key_control_and_pause.c \
					visualization_start_and_end.c	flag_searcher.c \
					stdout_stuff.c	corewar.c	sound_stuff.c

VM_INS_SRC		=	live.c	ld.c	st.c	add.c	sub.c	and.c	or.c \
					xor.c	zjmp.c	ldi.c	sti.c	fork.c	lld.c	lldi.c \
					lfork.c	aff.c		fn.c	iterate.c

PRINTF_SRC		=	ft_printf.c	put_signed_num.c	put_str_char.c \
					put_unsigned_num.c	put_wide.c	small_functions.c

ASM_SRC			=	main.c		op.c	get_labels_and_opcodes.c \
					validate_and_translate_into_machine_code.c	error.c \
					check_seperator_after_argument.c opcode_to_machine_code.c \
					get_values.c	is_reg_dir_ind.c	small_functions.c \
					translate_all_files_in_directory.c	reverse.c \
					write_arguments.c

CMP_SRC			=	cmp.cpp

CC				=	gcc
FLAGS			=	
NCURSES_FLAG	=	-lncurses
VFLAGS			=	-lmlx -framework OpenGL -framework AppKit -Ofast -O3

VM_OBJ			=	$(addprefix $(VM_OBJ_DIR), $(VM_SRC:.c=.o))
VM_INS_OBJ		=	$(addprefix $(VM_OBJ_DIR), $(VM_INS_SRC:.c=.o))
VM_PRINT_OBJ	=	$(addprefix $(VM_OBJ_DIR), $(PRINTF_SRC:.c=.o))
ASM_OBJ			=	$(addprefix $(ASM_OBJ_DIR), $(ASM_SRC:.c=.o))
CMP_OBJ			=	$(addprefix $(CMP_DIR), $(CMP_SRC:.cpp=.o))
INC_FILES		=	$(addprefix $(INC_DIR), $(INC))

VM_SRC_DIR		=	./vm_src/
VM_INS_SRC_DIR	=	./vm_src/instructions/
ASM_SRC_DIR		=	./asm_src/
VM_OBJ_DIR		=	./vm_obj/
ASM_OBJ_DIR		=	./asm_obj/
PRINTF_DIR		=	./vm_src/printf/
CMP_DIR			=	./cmp_src/
INC_DIR			=	./includes/
INC				=	asm.h	corewar.h	op.h

NC				=	\033[0m
BLUE			=	\033[3;36m
RED				=	\033[3;31m

all: $(VM) $(ASM)

$(VM_OBJ_DIR)%.o: $(VM_SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(VM_OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(VM_OBJ_DIR)%.o: $(VM_INS_SRC_DIR)%.c $(INC_FILES)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(VM_OBJ_DIR)%.o: $(PRINTF_DIR)%.c
	@$(CC) $(FLAGS) -o $@ -c $<

$(VM): $(VM_OBJ) $(VM_INS_OBJ) $(VM_PRINT_OBJ)
	@echo "${BLUE}Compiling $(VM) with $(FLAGS) flags${NC}\n..."
	@$(CC) $(FLAGS) $(NCURSES_FLAG) -o $(VM) $(VM_OBJ) $(VM_INS_OBJ) $(VM_PRINT_OBJ)
	@echo "${BLUE}Done!${NC}"

$(ASM_OBJ_DIR)%.o: $(ASM_SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(ASM_OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(ASM): $(ASM_OBJ)
	@echo "${BLUE}Compiling $(ASM) with $(FLAGS) flags${NC}\n..."
	@$(CC) $(FLAGS) -o $(ASM) $(ASM_OBJ)
	@echo "${BLUE}Done!${NC}"

$(CMP_DIR)%.o: $(CMP_DIR)%.cpp
	@clang++ $(FLAGS) -std=c++11 -o3 -ofast -o $@ -c $<

$(CMP): $(CMP_OBJ)
	@echo "${BLUE}Compiling $(CMP) with $(FLAGS) flags${NC}\n..."
	@clang++ $(FLAGS) -o $(CMP) $(CMP_OBJ)
	@echo "${BLUE}Done!${NC}"

clean:
	@rm -rf $(VM_OBJ_DIR) $(ASM_OBJ_DIR) $(CMP_OBJ)
	@echo  "${RED}$(VM_OBJ_DIR), $(ASM_OBJ_DIR) and $(CMP_OBJ) has been removed.${NC}"

fclean: clean
	@rm -rf $(VM) $(ASM) $(CMP)
	@echo "${RED}$(VM) $(ASM) and $(CMP) has been removed.${NC}"

re: fclean all

.PHONY: all clean fclean re
