/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:21:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/05 18:13:54 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h> // удалить в конце

# include "../libft/libft.h"
# include "op.h"
# include "disasm.h" // надо же?

# define ERR_FILE_NAME		1
# define ERR_CREATE_FILE	2
# define OP(index)			g_op_tab[index] // ne ebu

typedef struct			s_player
{
    int                 id; // номер игрока
    t_disasm            *champ; // инфа из дизасм
}						t_player;

typedef struct			s_vm
{
	char				arena[MEM_SIZE + 1]; // арена
    t_player            *player; // массив чемпионов
}						t_vm;


#endif