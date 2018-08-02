# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/04 17:34:26 by rnaumenk          #+#    #+#              #
#    Updated: 2017/11/22 16:06:01 by rnaumenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRC_DIR	=	./src/
OBJ_DIR	=	./obj/
INC_DIR	=	./include/
SRC		= 	ft_atoi.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_bzero.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memdel.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_memcmp.c \
			ft_putchar_fd.c \
			ft_putchar.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putstr_fd.c \
			ft_memmove.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_strclr.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strdel.c \
			ft_strcpy.c \
			ft_strequ.c \
			ft_striter.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strlen.c \
			ft_strcmp.c \
			ft_strjoin.c \
			ft_strmapi.c \
			ft_strmap.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strlcat.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strsub.c \
			ft_strstr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_lstnew.c \
			ft_lstmap.c \
			ft_lstiter.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_intlen.c \
			ft_factorial.c \
			ft_sqrt.c \
			ft_atoi_base.c \
			ft_sort_int_tab.c \
			ft_strrev.c \
			ft_print_bits.c \
			ft_max.c \
			ft_swap_bits.c \
			ft_isprime.c \
			ft_add_prime_sum.c \
			ft_list_size.c \
			ft_ispresent.c \
			ft_pgcd.c \
			ft_print_hex.c \
			ft_split_whitespaces.c \
			ft_list_foreach.c \
			ft_power.c \
			ft_lstadd_nth.c \
			ft_lstadd_end.c \
			ft_lstdel_nth.c \
			ft_lstdel_end.c \
			ft_lstrev.c \
			ft_lstsplit.c \
			ft_abs.c \
			ft_itoa_base.c \
			get_next_line.c \
			ft_swap.c \
 			check_the_buf_printf.c \
			check_the_flags_printf.c \
			check_the_width_printf.c \
			ft_litoa_base_printf.c \
			ft_printf.c \
			ft_uixtoa_base_printf.c \
			ft_ulxtoa_base_printf.c \
			functs1_printf.c \
			functs2_printf.c \
			functs3_printf.c \
			functs4_printf.c \
			functs5_printf.c \
			functs6_printf.c \
			functs7_printf.c \
			look_for_specificators_printf.c \
			prefunct1_printf.c \
			prefunct2_printf.c \
			prefunct3_printf.c \
			additional_printf.c
OBJ		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)libft.h
	@mkdir -p $(OBJ_DIR)
	@gcc -Wall -Wextra -Werror -o $@ -c $<

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
