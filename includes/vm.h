/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:21:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/21 20:13:41 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/libft.h"
# include "op.h"
# include <ncurses.h>

# define ERR_FILE_NAME		1
# define ERR_MAX_PLAYERS    2
# define ERR_FLAG			3
# define ERR_OPEN_FILE		4
# define ERR_MAGIC_HEADER	5
# define ERR_NAME			6
# define ERR_COMMENT		7
# define ERR_CHAMP_SIZE		8
# define ERR_MALLOC			9
# define OP(index)			g_op_tab[index]

/*
**	*file_name	- название файла
**	id			- номер игрока
**	fd			- поток для чтения файла
**	champ_size	- размер исполняемого кода
**	i			- позиция игрока на арене
*/
typedef struct			s_player
{
	char				*file_name;
	int					id;
	int					fd;
	int					champ_size;
	int					i;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
}						t_player;

typedef struct			s_arg
{
	int					arg;
	int					type;
}						t_arg;

/*
**	regs[]		- регистры
**	cursor_id	- уникальный номер каретки
**	live_cycle	- номер цикла, в котором последний раз выполнялась команда live
**	op			- код операции, на которой стоит каретка
**	cycles_left	- кол-во циклов, оставшихся до исполнения текущей операции
**	i			- текущая позиция каретки на арене
**	op_size		- размер операции, на которой стоит каретка
**	color		- цвет каретки
*/
typedef struct			s_cursor
{
	int					regs[REG_NUMBER];
	int					cursor_id;
	int					carry;
	int					live_cycle;
	int					op;
	int					cycles_left;
	int					i;
	int					op_size;
	int					color;
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_arena
{
	unsigned char		i;
	int					color;
	int					prev_color;
}						t_arena;

/*
**	player[]	- массив чемпионов
**	n_players	- количество чемпионов
**	*cur		- список кареток
**	cycle		- номер цикла
**	cycles_to_die - циклов в периоде до проверки
**	n_live		- количество live за последний период
**	n_check		- количество проверок
**	winner		- победитель
**	dump		- флаг -dump
**	v			- флаг визуализации
**	v_cycle		- цикл, с которого запускается визуализация
**	d			- флаг дебага (2 выводит всё, 1 - финальное количество циклов)
*/
typedef struct			s_vm
{
	t_arena				arena[MEM_SIZE + 1];
	int					n_players;
	t_player			player[MAX_PLAYERS];
	t_cursor			*cur;
	int					cycle;
	int					cycles_to_die;
	int					n_live;
	int					n_check;
	int					winner;
	int					dump;
	int					v;
	int					v_cycle;
	int					d;
}						t_vm;

/*
**	parse_args.c
*/
int						parse_args(t_vm *vm, int ac, char **av);

/*
**	parse_args_utils.c
*/
int						check_filename(char *name);
int						check_atoi(char *av);

/*
**	main.c
*/
void					print_arena(t_vm *vm);

/*
**	error.c
*/
int						error_vm(int error);
int						error_line(int error, char *str);
int						error_champ_size(t_player *player);

/*
**	create_players.c
*/
int						check_four_bytes(t_player *player);
int						check_player(t_player *player);
int						fill_arena(t_vm *vm, t_player player, int color);
int						create_player(t_vm *vm);

/*
**	game_cycle.c
*/
void					finish_game(t_vm *vm);
int						game_cycle(t_vm *vm);

/*
**	ncurses.c
*/
void					init_ncurses(void);
void					print_ncurses(t_vm *vm, int end, int i);
/*
**	create_cursor.c
*/
int						malloc_cursor(t_vm *vm);
int						create_cursors(t_vm *vm);

/*
**	cursor_op.c
*/
int						count_size_arg_code(t_vm *vm, int op, int i);
int						count_size(t_vm *vm, int op, int i);
void					cycles_less_zero(t_vm *vm, t_cursor *tmp);
int						cursor_op(t_vm *vm);

/*
**	check_ops.c
*/
int						check_position(int pos);
int						write_args(t_vm *vm, t_cursor *cur, t_arg *args,
						int num_args);
int						arg_to_type(t_vm *vm, t_cursor *cur, int bytes, int j);
int						write_types(t_vm *vm, t_cursor *cur, t_arg *args,
						int num_args);
int						check_op(t_vm *vm, t_cursor *cur);

/*
**	send_to_op.c
*/
void					send_to_op(t_vm *vm, t_cursor *cur, t_arg args[]);

/*
**	op_tools.c
*/
int						get_arg(t_vm *vm, int i, int size);
void					write_to_memory(t_vm *vm, t_cursor *cur, int reg,
						int address);
int						set_arg(t_vm *vm, t_cursor *cur, t_arg args[], int i);

/*
**	op_live_ls_st_add_sub.c
*/
void					op_live(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_ld(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_st(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_add(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_sub(t_vm *vm, t_cursor *cur, t_arg *args);

/*
**	op_ldi_sti_lld_lldi.c
*/
void					op_ldi(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_sti(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_lld(t_vm *vm, t_cursor *cur, t_arg *args);
void					op_lldi(t_vm *vm, t_cursor *cur, t_arg *args);

/*
**	op_and_or_xor_zjmp.c
*/
void					op_and(t_vm *vm, t_cursor *cur, t_arg args[]);
void					op_or(t_vm *vm, t_cursor *cur, t_arg args[]);
void					op_xor(t_vm *vm, t_cursor *cur, t_arg args[]);
void					op_zjmp(t_vm *vm, t_cursor *cur, t_arg args[]);

/*
**	op_fork_lfork_aff.c
*/
void					op_fork(t_vm *vm, t_cursor *cur, t_arg args[]);
void					op_lfork(t_vm *vm, t_cursor *cur, t_arg args[]);
void					op_aff(t_vm *vm, t_cursor *cur, t_arg args[]);

/*
** print_corewar.c
*/
void					introduce_players(t_vm *vm);
void					print_arena(t_vm *vm);
void					declare_winner(t_vm *vm);

#endif
