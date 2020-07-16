/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 20:44:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/16 20:27:27 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "../includes/vm.h"

void	init_ncurses()
{
	initscr();
	noecho();
	cbreak();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	init_pair(9, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_BLUE);
	init_pair(11, COLOR_RED, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_RED);
	init_pair(13, COLOR_WHITE, COLOR_BLACK);
	init_pair(14, COLOR_BLACK, COLOR_WHITE);
	curs_set(0);
}

void	print_players_ncurses(t_vm *vm, WINDOW *info)
{
	int j;

	j = 0;
	while (j < vm->n_players)
	{
		wattron(info, A_BOLD);
		wprintw(info, "Player %d: ", j + 1);
		wattron(info, COLOR_PAIR(j * 2 + 1));
		wprintw(info, "%s\n", vm->player[j].name);
		wattroff(info, A_BOLD);
		wattroff(info, COLOR_PAIR(j * 2 + 1));
		j++;
	}
	wattron(info, A_BOLD);
	wprintw(info, "\nCycles: %d\n", vm->cycle);
	wattroff(info, A_BOLD);
	wrefresh(info);
}

void	print_end_ncurses(t_vm *vm, WINDOW *info)
{
	int winner;

	if (!vm->winner)
		winner = vm->n_players - 1;
	else
		winner = vm->winner - 1;
	wattron(info, A_BOLD);
	wprintw(info, "\n*** PLAYER ***\n");
	wattron(info, COLOR_PAIR(winner * 2 + 1));
	wprintw(info, "%s", vm->player[winner].name);
	wattroff(info, COLOR_PAIR(winner * 2 + 1));
	wprintw(info, "\n***  WON  ***\n");
	wattroff(info, A_BOLD);
	wrefresh(info);
}

void	print_ncurses(t_vm *vm, int end)
{
	int		i;
	WINDOW	*arena;
	WINDOW	*info;

	i = 0;
	arena = newwin(65, 191, 0, 0);
	info = newwin(64, 84, 0, 195);
	if (vm->v)
	{
		erase(); // или лучше clear ? проверить
		end == 1 ? print_end_ncurses(vm, info) : print_players_ncurses(vm, info);
		while (i < MEM_SIZE)
		{
			wattron(arena, COLOR_PAIR(vm->arena[i].color));
			wprintw(arena, "%.2x", vm->arena[i].i);
			wattroff(arena, COLOR_PAIR(vm->arena[i].color));
			i++;
			if (i % 64 != 0 || i == 0)
				wprintw(arena, " ");
		}
		wprintw(arena, "\n");
		wrefresh(arena);
		// usleep(10000);
	}
	delwin(arena);
	delwin(info);
}
