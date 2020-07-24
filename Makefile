# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 16:37:34 by croxana           #+#    #+#              #
#    Updated: 2020/07/24 20:53:44 by tpepperm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm

DISASM = disasm

VM = corewar

RES_ASM = main.c read_file.c find_name_comment.c name_comment_utils.c error.c parse_commands.c \
	find_label.c check_command.c find_args.c op.c check_comm_list.c write_to_file.c \
	find_args_utils.c

SRC_ASM = $(addprefix src_asm/,$(RES_ASM))

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
	ft_printf_f.c ft_printf_func.c ft_printf_color.c ft_printf_b.c ft_free_split.c \
	ft_fdprintf.c ft_fdprintf_b_c_per.c ft_fdprintf_di.c ft_fdprintf_f.c \
	ft_fdprintf_p_s.c ft_fdprintf_u.c ft_fdprintf_x_o.c)

RES_DISASM = main.c error.c parse_file.c parse_commands.c op.c write_file.c \
	new_comm_arg.c

SRC_DISASM = $(addprefix src_disasm/,$(RES_DISASM))

RES_VM = main.c error.c parse_args.c create_players.c game_cycle.c ncurses.c op.c \
	create_cursor.c cursor_op.c check_ops.c send_to_op.c op_live_ls_st_add_sub.c \
	op_ldi_sti_lld_lldi.c op_fork_lfork_aff.c op_and_or_xor_zjmp.c op_tools.c \
	parse_args_utils.c print_corewar.c
	
SRC_VM = $(addprefix src_vm/,$(RES_VM))

INC_ASM = includes/asm.h

INC_OP = includes/op.h

INC_DISASM = includes/disasm.h

INC_VM = includes/vm.h

INC_LIB = libft/libft.h

LIBFT = libft/libft.a

FLAG = -Wall -Werror -Wextra

all: $(ASM) $(DISASM) $(VM)

$(LIBFT): $(SRC_LIB) $(INC_LIB)
	@make -C libft/
	@echo "\x1b[33mLibft is ready\x1b[0m"

$(ASM): $(SRC_ASM) $(INC_ASM) $(LIBFT) $(INC_OP)
	@gcc -o $(ASM) $(FLAG) -I $(INC_ASM) $(SRC_ASM) $(LIBFT)
	@echo "\x1b[32mAssembler is ready\x1b[0m"

$(DISASM): $(SRC_DISASM) $(INC_DISASM) $(LIBFT) $(INC_OP)
	@gcc -o $(DISASM) $(FLAG) -I $(INC_DISASM) $(SRC_DISASM) $(LIBFT)
	@echo "\x1b[35mDisassembler is ready\x1b[0m"

$(VM): $(SRC_VM) $(INC_VM) $(LIBFT) $(INC_OP)
	@gcc -o $(VM) $(FLAG) -I $(INC_VM) $(SRC_VM) $(LIBFT) -lncurses
	@echo "\x1b[36mVirtual Machine is ready\x1b[0m"

clean:
	@rm -f libft/*.o

fclean: clean
	@rm -f $(LIBFT) $(ASM) $(DISASM) $(VM)

re: fclean all

