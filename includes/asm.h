/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:27:56 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/07 18:04:06 by tkarpukova       ###   ########.fr       */
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
	int 			arg;
	char			*arg_name;
	struct s_args 	*next;
}					t_args;

typedef struct  		s_command
{
	t_label				*label;
	int					size;
	unsigned char		op;
	unsigned char		args_type;
	t_args				*args;
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
int		read_file(t_asm *asmb, char *file_name);

/*
** error.c
*/
int		error_line(int error, t_gnl *gnl, int return_num);
int		length_error(int index, int length);

/*
** find_name_comment.c
*/
int		check_next_line(char *line, int j, t_gnl **tmp, int length);
int		create_name_comment(char *line, char *name_com, t_gnl **tmp, int length);
int		proceed_name_comment(t_gnl **tmp, int i, t_asm *asmb);
int		find_name_comment(t_asm *asmb);

/*
** name_comment_utils.c
*/
int		is_space(char c);
int		check_end_space(char *line);
int     skip_first_spaces(char *line);

/*
** parse_commands.c
*/
int		new_command(t_asm *asmb);
int		parse_commands(t_asm *asmb);

/*
** find_label.c
*/
int		malloc_label(t_command *command);
int		find_label(t_asm *asmb);

/*
** check_command.c
*/
int			find_command(t_asm *asmb);
int			check_command(t_asm *asmb);


#endif
