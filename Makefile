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

VM_SRC			=	main.c		change_bot_order.c	parse_arguments.c \
					visualization.c		read_cor_files.c	op.c

VM_INS_SRC		=	add.c	sub.c ld.c sti.c

ASM_SRC			=	main.c		op.c	get_labels_and_opcodes.c \
					validate_and_translate_into_machine_code.c	error.c \
					check_seperator_after_argument.c opcode_to_machine_code.c \
					get_values.c	is_reg_dir_ind.c	small_functions.c \
					translate_all_files_in_directory.c	reverse.c \
					write_arguments.c

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra
NCURSES_FLAG	=	-lncurses
VFLAGS			=	-lmlx -framework OpenGL -framework AppKit -Ofast -O3

VM_OBJ			=	$(addprefix $(VM_OBJ_DIR), $(VM_SRC:.c=.o))
VM_INS_OBJ		=	$(addprefix $(VM_OBJ_DIR), $(VM_INS_SRC:.c=.o))
ASM_OBJ			=	$(addprefix $(ASM_OBJ_DIR), $(ASM_SRC:.c=.o))

VM_SRC_DIR		=	./vm_src/
VM_INS_SRC_DIR	=	./vm_src/instructions/
ASM_SRC_DIR		=	./asm_src/
VM_OBJ_DIR		=	./vm_obj/
ASM_OBJ_DIR		=	./asm_obj/
INC_DIR			=	./includes/

NC				=	\033[0m
BLUE			=	\033[3;36m
RED				=	\033[3;31m

# IN 				= 	gcc -o vm_src/main.o -c vm_src/main.c -I includes

# INS				=	gcc -o vm_obj/add.o -c vm_src/instructions/add.c -I includes

all: $(VM) $(ASM)

$(VM_OBJ_DIR)%.o: $(VM_SRC_DIR)%.c
	@mkdir -p $(VM_OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(VM_OBJ_DIR)%.o: $(VM_INS_SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(VM): $(VM_OBJ) $(VM_INS_OBJ)
	@echo "${BLUE}Compiling $(VM) with $(FLAGS) flags${NC}\n..."
	@$(CC) $(FLAGS) $(NCURSES_FLAG) -o $(VM) $(VM_OBJ) $(VM_INS_OBJ)
	@echo "${BLUE}Done!${NC}"

$(ASM_OBJ_DIR)%.o: $(ASM_SRC_DIR)%.c
	@mkdir -p $(ASM_OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(ASM): $(ASM_OBJ)
	@echo "${BLUE}Compiling $(ASM) with $(FLAGS) flags${NC}\n..."
	@$(CC) $(FLAGS) -o $(ASM) $(ASM_OBJ)
	@echo "${BLUE}Done!${NC}"

clean:
	@rm -rf $(VM_OBJ_DIR) $(ASM_OBJ_DIR)
	@echo  "${RED}$(VM_OBJ_DIR) and $(ASM_OBJ_DIR) has been removed.${NC}"

fclean: clean
	@rm -rf $(VM) $(ASM)
	@echo "${RED}$(VM) and $(ASM) has been removed.${NC}"

re: fclean all

.PHONY: all clean fclean re
