/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:21:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/08 16:04:46 by tkarpukova       ###   ########.fr       */
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
# define ERR_OPEN_FILE		4
# define ERR_MAGIC_HEADER	5
# define ERR_NAME			6
# define ERR_COMMENT		7
# define ERR_MAX_SIZE		8
# define ERR_CHAMP_SIZE		9
# define OP(index)			g_op_tab[index] // ne ebu

typedef struct			s_player
{
	char				*file_name;
	int					id; // номер игрока
	int					fd;
	int					champ_size;
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

typedef struct			s_arena
{
	unsigned char		i;
	int					color;
	int					cursor;
}						t_arena;

typedef struct			s_vm
{
	t_arena				arena[MEM_SIZE + 1]; // арена
	int					cycle; // номер цикла
	int					v; // флаг визуализации
	int					dump; // флаг -dump
	int					cycles_to_die; // циклов в периоде до проверки
	int					n_live; // количество live за последний период
	int					n_check; // количество проверок
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
int     error_line(int error, char *str);

/*
** create_players.c
*/
int		check_four_bytes(t_player *player);
int		check_player(t_player *player);
int		fill_arena(t_vm *vm, t_player player);
int		create_player(t_vm *vm);

/*
**	game_cycle.c
*/
int			game_cycle(t_vm *vm);

#endif