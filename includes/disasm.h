/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:22:42 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/01 23:22:44 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

# include <stdio.h> // удалить в конце

# include "../libft/libft.h"
# include "op.h"

typedef struct 		s_arg
{
	int				type; //T_REG, T_IND, T_DIR
	int 			arg; //значение аргумента
	struct s_arg 	*next;
}					t_arg;

typedef struct  		s_op
{
	unsigned char		op_code; //код команды
	t_arg				*args; //аргументы
	struct s_command	*next;
}						t_op;

typedef struct          s_disasm
{
      char              *name;
      char              *comment;
      int               prog_length;
      t_op				*ops; 
}                       t_disasm;


#endif