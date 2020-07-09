/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/09 15:29:52 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

// parse_args: 
// + проверить имя файлов - DONE
// + проверить, что есть игроки и их кол-во <= MAX_PLAYERS - DONE
// + обработать флаги (-n, -dump, -v) - DONE
// + записать туда номер игрока, имя, коммент, позицию на арене = проверить имя, коммент, размер - DONE 
// + если все ок, записать код чемпиона в арену - DONE
// - все каретки создать, записать туда номер игроков и все остальные данные (?)
// - поставить каретки на начало кодов чемпионов
// + вывести арену (можно сразу в ncurses) - DONE (пока без ncurses)
// parse_args()

// прописать все команды

void	print_arena(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%0.2x ", vm->arena[i].i);
		i++;
		if (i % 64 == 0)
			printf("\n");
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	ft_memset(&vm, 0, sizeof(vm));
	if (parse_args(&vm, argc, argv) &&
		create_player(&vm) && 
		create_cursors(&vm))
	{
		// if (vm.v)
		// 	start_ncurses(&vm);
		// else
		// 	print_arena(&vm);
		printf("game cycle\n");; //если ошибок нет, запускается цикл игры
		game_cycle(&vm);
	}
	// free_all(&vm);
	return (0);
}