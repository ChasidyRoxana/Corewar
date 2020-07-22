/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:22:42 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/22 22:03:45 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include "../libft/libft.h"
# include "op.h"

# define ERR_USAGE		1
# define ERR_FILE_NAME	2
# define ERR_OPEN_FILE	3
# define ERR_HEADER		4
# define ERR_COMMAND	5
# define ERR_CRT_FILE	6
# define ERR_CHAMP_SIZE	7
# define OP(index)		g_op_tab[index]

/*
**	type	- T_REG, T_IND, T_DIR
**	arg		- значение аргумента
*/
typedef struct			s_arg
{
	int					type;
	int					arg;
	struct s_arg		*next;
}						t_arg;

/*
**	op_code	- код команды
**	*args	- аргументы
*/
typedef struct			s_command
{
	int					op_code;
	t_arg				*args;
	struct s_command	*next;
}						t_command;

/*
**	*ops		- список команд
**	*ops_last	- указатель на последний элемент списка команд
*/
typedef struct			s_disasm
{
	char				*filename;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					prog_length;
	t_command			*ops;
	t_command			*ops_last;
}						t_disasm;

/*
** error.c
*/
int						error_disasm(int error);

/*
** parse_file.c
*/
int						parse_file(t_disasm *disasm, char *file);

/*
** parse_commands.c
*/
int						parse_commands(t_disasm *disasm, int fd);

/*
** new_comm_arg.c
*/
int						new_command(t_disasm *disasm);
int						new_arg(t_command *comm);

/*
** write_file.c
*/
int						write_to_file(t_disasm *disasm);

#endif
