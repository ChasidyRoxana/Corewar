/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:22:42 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/02 14:13:45 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include <stdio.h> // удалить в конце

# include "../libft/libft.h"
# include "op.h"

# define ERR_FILE_NAME	1

# define OP(index)		g_op_tab[index] // ne ebu

typedef struct 			s_arg
{
	int					type; //T_REG, T_IND, T_DIR
	int 				arg; //значение аргумента
	struct s_arg 		*next;
}						t_arg;

typedef struct  		s_command
{
	unsigned char		op_code; //код команды
	t_arg				*args; //аргументы
	struct s_command	*next;
}						t_command;

typedef struct          s_disasm
{
	char				*filename;
	char              	*name;
	char              	*comment;
	int               	prog_length;
	t_command			*ops; 
}                       t_disasm;

/*
** main.c
*/
int		check_filename(char *name);

/*
** error.c
*/
int     error_disasm(int error);

#endif