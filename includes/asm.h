/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:27:56 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/24 18:47:01 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "op.h"

# define ERR_OPEN_FILE			1
# define ERR_MALLOC				2
# define ERR_FILE				3
# define ERR_FILE_NAME			4
# define ERR_NAME_LENGTH		5
# define ERR_COMMENT_LENGTH		6
# define ERR_NO_NAME_COMMENT	7
# define ERR_NOT_COMMAND		8
# define ERR_NO_END				9
# define ERR_NAME				10
# define ERR_COMMENT			11
# define ERR_SYNTAX				12
# define ERR_REG				13
# define ERR_LEXICAL			14
# define ERR_LABEL				15
# define ERR_OP					16
# define ERR_ARG				17
# define ERR_MAX_ARG			18
# define ERR_MIN_ARG			19
# define ERR_NO_ARGS			20
# define ERR_NO_OP				21
# define ERR_CREATE_FILE		22

# define OP(index)	g_op_tab[index]

typedef struct			s_gnl
{
	int					nb_line;
	char				*line;
	struct s_gnl		*next;
}						t_gnl;

typedef struct			s_label
{
	char				*line;
	struct s_label		*next;
}						t_label;

/*
** type 	- T_REG, T_IND, T_DIR
** arg 		- число, которое потом запишем в файл
** *arg_name - как было записано в команде
*/
typedef struct			s_args
{
	int					type;
	int					arg;
	char				*arg_name;
	struct s_args		*next;
}						t_args;

/*
** *label 		- список названий меток для этой команды
** size 		- размер команды
** op 			- код команды
** args_type 	- код аргументов
** num_args 	- количетво аргуентов
** *gnl_line 	- указатель на строку гнл с этой командой
** *args 		- аргументы
*/
typedef struct			s_command
{
	t_label				*label;
	int					size;
	unsigned char		op;
	unsigned char		args_type;
	int					num_args;
	t_gnl				*gnl_line;
	t_args				*args;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct			s_asm
{
	t_gnl				*gnl;
	t_gnl				*gnl_last;
	t_command			*comm;
	t_command			*comm_last;
	t_header			header;
	char				*filename;
	int					flag_name;
	int					flag_comment;
}						t_asm;

/*
** read file.c
*/
int						read_file(t_asm *asmb, char *file_name);

/*
** error.c
*/
int						error_common(int error);
int						error_line(int error, t_gnl *gnl, int n_sym);
int						error_args(int error, t_command *comm, char *str,
						int n_sym);
int						length_error(int index, int length);

/*
** find_name_comment.c
*/
int						check_next_line(char *line, int j, t_gnl **tmp,
						int length);
int						create_namecom(char *line, char *name_com, t_gnl **tmp,
						int length);
int						check_name_comment(t_gnl **tmp, int i, t_asm *asmb,
						int length);
int						proceed_name_comment(t_gnl **tmp, int i, t_asm *asmb);
int						find_name_comment(t_asm *asmb);

/*
** name_comment_utils.c
*/
int						is_separator(char c);
int						is_args(char c);
int						is_space(char c);
int						check_end_space(char *line);
int						skip_first_spaces(char *line);

/*
** parse_commands.c
*/
int						new_command(t_asm *asmb);
int						parse_commands(t_asm *asmb);
int						delete_empty_lines(t_asm *asmb);

/*
** find_label.c
*/
int						malloc_label(t_command *command);
int						create_label(t_asm *asmb, t_gnl *tmp, int *i);
int						find_label(t_asm *asmb);
int						is_comment(char c);
int						is_found(t_asm *asmb, t_gnl *tmp, int i);

/*
** check_command.c
*/
int						check_op_name(char *com);
int						find_command(t_asm *asmb, char *line);
int						check_command(t_asm *asmb);

/*
** find_args.c
*/
int						new_args(t_command *command);
int						write_arg(t_asm *asmb, t_args *tmp, int *i,
						int index_op);
int						double_check_args(t_asm *asmb, int *i);
int						proceed_args(t_asm *asmb, t_args *tmp, int *i,
						int index_op);
int						find_args(t_asm *asmb, int i, int index_op);

/*
** find_args_utils.c
*/
int						is_numeric(char c);
int						check_numeric(t_asm *asmb, int *err, int *i, int *last);
int						parse_args(t_asm *asmb, t_args *tmp, int *i,
						int index_op);
int						check_atoi(char *av);

/*
** check_comm_list.c
*/
int						check_comm_list(t_asm *asmb);

/*
** write_to_file.c
*/
int						write_to_file(t_asm *asmb);
void					write_int(int fd, unsigned int num, int byte);

#endif
