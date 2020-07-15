# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 15:19:12 by croxana           #+#    #+#              #
#    Updated: 2020/01/07 13:48:25 by tpepperm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
	  ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memcmp.c \
	  ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_power.c \
	  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	  ft_strcat.c ft_strcdup.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
	  ft_strdel.c ft_strdup.c ft_strequ.c ft_strjoin.c ft_strlcat.c\
	  ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c\
	  ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c\
	  ft_strsub.c ft_strtrim.c ft_swap.c get_next_line.c\
	  ft_printf.c ft_printf_flags.c ft_printf_c.c ft_printf_s.c ft_printf_p.c \
	  ft_printf_per.c ft_printf_x.c ft_printf_o.c ft_printf_u.c ft_printf_di.c \
	  ft_printf_f.c ft_printf_func.c ft_printf_color.c ft_printf_b.c ft_free_split.c \
	  ft_fdprintf.c ft_fdprintf_b_c_per.c ft_fdprintf_di.c ft_fdprintf_f.c \
	  ft_fdprintf_p_s.c ft_fdprintf_u.c ft_fdprintf_x_o.c

FLAG = -Wall -Werror -Wextra

OBG = ft_atoi.o ft_itoa.o ft_lstadd.o ft_lstdel.o ft_lstdelone.o ft_lstiter.o \
	  ft_lstmap.o ft_lstnew.o ft_memalloc.o ft_memccpy.o ft_memcmp.o \
	  ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o ft_power.o \
	  ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o \
	  ft_strcat.o ft_strcdup.o ft_strchr.o ft_strclr.o ft_strcmp.o ft_strcpy.o \
	  ft_strdel.o ft_strdup.o ft_strequ.o ft_strjoin.o ft_strlcat.o\
	  ft_strlen.o ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnequ.o\
	  ft_strnew.o ft_strnstr.o ft_strrchr.o ft_strsplit.o ft_strstr.o\
	  ft_strsub.o ft_strtrim.o ft_swap.o get_next_line.o\
	  ft_printf.o ft_printf_flags.o ft_printf_c.o ft_printf_s.o ft_printf_p.o \
	  ft_printf_per.o ft_printf_x.o ft_printf_o.o ft_printf_u.o ft_printf_di.o \
	  ft_printf_f.o ft_printf_func.o ft_printf_color.o ft_printf_b.o ft_free_split.o \
	  ft_fdprintf.o ft_fdprintf_b_c_per.o ft_fdprintf_di.o ft_fdprintf_f.o \
	  ft_fdprintf_p_s.o ft_fdprintf_u.o ft_fdprintf_x_o.o

INC = libft.h

all: $(NAME)

$(NAME): $(SRC) $(INC)
	@gcc -c -I $(INC) $(FLAG) $(SRC)
	@ar rc $(NAME) $(OBG)
	@ranlib $(NAME)

clean:
	@rm -f $(OBG)

fclean: clean
	@rm -f $(NAME)

re: fclean all
