# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 16:37:34 by croxana           #+#    #+#              #
#    Updated: 2020/05/05 13:35:54 by tkarpukova       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# заменить шапку

ASM = asm

RES = main.c read_file.c find_name_comment.c name_comment_utils.c error.c
# op.c

SRC = $(addprefix src_asm/,$(RES))

SRC_LIB = $(addprefix libft/,ft_atoi.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
	  ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memcmp.c \
	  ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_power.c \
	  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	  ft_strcat.c ft_strcdup.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
	  ft_strdel.c ft_strdup.c ft_strequ.c ft_strjoin.c ft_strlcat.c\
	  ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c\
	  ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c\
	  ft_strsub.c ft_strtrim.c ft_swap.c get_next_line.c\
	  ft_printf.c ft_printf_flags.c ft_printf_c.c ft_printf_s.c ft_printf_p.c \
	  ft_printf_per.c ft_printf_x.c ft_printf_o.c ft_printf_u.c ft_printf_di.c \
	  ft_printf_f.c ft_printf_func.c ft_printf_color.c ft_printf_b.c)

INC = includes/asm.h
# op.h ? - прописать зависимость

INC_LIB = libft/libft.h

LIBFT = libft/libft.a

FLAG = -Wall -Werror -Wextra

all: $(ASM)

$(LIBFT): $(SRC_LIB) $(INC_LIB)
	make -C libft/

$(ASM): $(SRC) $(INC) $(LIBFT)
	gcc -o $(ASM) $(FLAG) -I $(INC) $(SRC) $(LIBFT)

clean:
	@rm -f libft/*.o

fclean: clean
	@rm -f $(LIBFT) $(ASM)

re: fclean all

norm:
	@echo "\x1b[32mASM\x1b[0m"
	@norminette $(SRC) $(INC)