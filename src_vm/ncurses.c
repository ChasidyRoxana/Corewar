/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 20:44:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/14 17:33:54 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "../includes/vm.h"

void	init_ncurses()
{
	initscr();
	// noecho(); вроде не влияет ни на что, но по идее отключает отображение вводимых символов
	// инициализируем цветовые пары, чтобы позже к ним обращаться
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
	curs_set(0); // "убиваем" курсор
}

void	print_ncurses(t_vm *vm)
{
	int i = 0;

	if (vm->v)
	{
		erase(); // или лучше clear ? проверить
		while (i < MEM_SIZE)
		{
			// printw("%d", vm->arena[i].color);
			// printf("%d\n", vm->arena[i].color);
			attron(COLOR_PAIR(vm->arena[i].color));
			printw("%.2x", vm->arena[i].i);
			attroff(COLOR_PAIR(vm->arena[i].color));
			printw(" ");
			i++;
			if (i % 64 == 0)
				printw("\n");
		}
		refresh();
		// getch();
		// endwin();
	}
}

void	start_ncurses(t_vm *vm)
{
	init_ncurses();
	if (!vm)
		return ;
	// print_ncurses(vm);
}