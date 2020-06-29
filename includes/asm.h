/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:27:56 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/06/29 22:41:28 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdio.h> // удалить в конце

# include "../libft/libft.h"
# include "op.h"

# define ERR_OPEN_FILE			1
# define ERR_MALLOC				2
# define ERR_DOT				3
# define ERR_FILE_NAME			4
# define ERR_NAME_LENGTH		5
# define ERR_COMMENT_LENGTH		6
# define ERR_NAME				7
# define ERR_COMMENT			8
# define ERR_NO_NAME_COMMENT	9
# define ERR_NOT_COMMAND		10
# define ERR_ARG				12
# define ERR_SYNTAX				13
# define ERR_MAX_ARG			14
# define ERR_MIN_ARG			15
# define ERR_REG				16
# define ERR_NO_ARGS			17
# define ERR_LEXICAL			18
# define ERR_LABEL				19
# define ERR_OP					20
# define ERR_NO_END				21


# define OP(index)	g_op_tab[index] // ne ebu


typedef struct  	s_gnl
{
	int				nb_line;
	char			*line;
	struct s_gnl	*next;
}					t_gnl;

typedef struct 		s_label
{
	char			*line;
	struct s_label	*next;
}					t_label;

typedef struct 		s_args
{
	int				type; //T_REG, T_IND, T_DIR
	int 			arg; //число, которое потом запишем в файл
	char			*arg_name; //как было записано в команде
	struct s_args 	*next;
}					t_args;

typedef struct  		s_command
{
	t_label				*label; //список названий меток для этой команды
	int					size; //размер команды
	unsigned char		op; //код команды
	unsigned char		args_type; //код аргументов 
	int					num_args; //количетво аргуентов
	t_gnl				*gnl_line; //указатель на строку гнл с этой командой
	t_args				*args; //аргументы
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct  s_asm
{
	t_gnl		*gnl;
	t_gnl		*gnl_last;
	t_command	*comm;
	t_command	*comm_last;
	t_header	header;
	char		*filename;
	int			flag_name;//
	int			flag_comment;//
}				t_asm;

/*
** read file.c
*/
int			read_file(t_asm *asmb, char *file_name);

/*
** error.c
*/
int			error_line(int error, t_gnl *gnl, int return_num, int n_sym);
int			error_args(int error, t_gnl *gnl, t_command *comm, int n_sym);
int			error_without_gnl(int error, int return_num);
int			length_error(int index, int length);

/*
** find_name_comment.c
*/
int			check_next_line(char *line, int j, t_gnl **tmp, int length);
int			create_name_comment(char *line, char *name_com, t_gnl **tmp, int length);
int			proceed_name_comment(t_gnl **tmp, int i, t_asm *asmb);
int			find_name_comment(t_asm *asmb);

/*
** name_comment_utils.c
*/
int			is_separator(char c);
int			is_args(char c);
int			is_space(char c);
int			check_end_space(char *line);
int     	skip_first_spaces(char *line);

/*
** parse_commands.c
*/
int			new_command(t_asm *asmb);
int			parse_commands(t_asm *asmb);

/*
** find_label.c
*/
int			malloc_label(t_command *command);
int			find_label(t_asm *asmb);

/*
** check_command.c
*/
int			check_op_name(char *com);
int			find_command(t_asm *asmb, char *line);
int			check_command(t_asm *asmb);

/*
** find_args.c
*/
int			new_args(t_command *command);
int			write_arg(t_asm *asmb, t_args *tmp, int *i, int index_op);
int			double_check_args(t_asm *asmb, int *i);
int			proceed_args(t_asm *asmb, t_args *tmp, int *i, int index_op);
int			find_args(t_asm *asmb, int i, int index_op);

/*
** check_comm_list.c
*/
int			check_comm_list(t_asm *asmb);

/*
** write_to_file.c
*/
int			write_to_file(t_asm *asmb);
void		write_int(int fd, unsigned int num, int byte);

#endif
