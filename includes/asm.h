/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:27:56 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/04 16:47:13 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdio.h> // удалить в конце

# include "libft.h"
# include "op.h"

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
	struct s_args 	*next;
}					t_args;

typedef struct  		s_command
{
	t_label				*label;
	int					size;
	unsigned char		op;
	unsigned char		args_type;
	t_args				*args;
	struct s_command	*next;
}						t_command;

typedef struct  s_asm
{
	t_gnl		*gnl;
	t_command	*commands;
	t_header	header;
}				t_asm;

#endif
