/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:21:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/07 21:47:55 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h> // удалить в конце

# include "../libft/libft.h"
# include "op.h"

# define ERR_FILE_NAME		1
# define ERR_MAX_PLAYERS    2
# define ERR_FLAG			3
# define OP(index)			g_op_tab[index] // ne ebu

typedef struct			s_player
{
	char				*file_name;
	int					id; // номер игрока
	int					fd;
	int					i; // позиция игрока на арене
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
}						t_player;

typedef struct			s_cursor
{
	int					regs[REG_NUMBER]; // регистры
	int					player_id; // номер игрока 
	int					carry;
	int					live_cycle; // номер цикла, в котором последний раз выполнялась команда live
	int					op; // код операции, на которой стоит каретка
	int					cycles_left; // кол-во операций, оставшихся до исполнения операции на которой стоит каретка
	int					i; // текущая позиция каретки
	int					op_size; // размер операции, на которой стоит каретка
	
	// добавить цвет
}						t_cursor;

typedef struct			s_vm
{
	unsigned char		arena[MEM_SIZE + 1]; // арена
	int					cycle; // номер цикла
	int					visu; // флаг визуализации
	int					dump; // флаг -dump
	int					n_players;
	t_player			player[MAX_PLAYERS]; // массив чемпионов
	t_cursor			*cur;
}						t_vm;

/*
**	parse_args.c
*/
int			parse_args(t_vm *vm, int ac, char **av);

/*
** main.c
*/

/*
** error.c
*/
int     error_vm(int error);

#endif