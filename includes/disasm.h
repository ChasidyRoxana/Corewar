/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:22:42 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/05 18:41:37 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include <stdio.h> // удалить в конце

# include "../libft/libft.h"
# include "op.h"

# define ERR_FILE_NAME		1
# define ERR_CREATE_FILE	2
# define OP(index)			g_op_tab[index] // ne ebu

typedef struct			s_arg
{
	int					type; //T_REG, T_IND, T_DIR
	int 				arg; //значение аргумента
	struct s_arg 		*next;
}						t_arg;

typedef struct			s_command
{
	int					op_code; //код команды
	t_arg				*args; //аргументы
	struct s_command	*next;
}						t_command;

typedef struct			s_disasm
{
	char				*filename;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					prog_length;
	char				*exec_code; // исполняемый код чемпиона
	t_command			*ops;
	t_command			*ops_last;
}						t_disasm;

/*
** main.c
*/
int			check_filename(t_disasm *disasm, char *name);

/*
** start_disasm.c
*/
int			start_disasm(t_disasm *disasm, char *filename);
int			check_filename(t_disasm *disasm, char *name);

/*
** error.c
*/
int			error_disasm(int error);

/*
** parse_file.c
*/
int			parse_file(t_disasm *disasm, char *file);

/*
** parse_commands.c
*/
int			parse_commands(t_disasm *disasm, int fd);

/*
** new_comm_arg.c
*/
int			new_command(t_disasm *disasm);
int			new_arg(t_command *comm);

/*
** write_file.c
*/
int			write_to_file(t_disasm *disasm);

#endif