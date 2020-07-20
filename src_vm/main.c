/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/20 20:24:03 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	free_all(t_vm *vm)
{
	t_cursor	*tmp;

	while (vm->cur)
	{
		tmp = vm->cur;
		vm->cur = vm->cur->next;
		free(tmp);
	}
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	ft_memset(&vm, 0, sizeof(vm));
	vm.n_check = 1;
	vm.cycle = 1;
	vm.cycles_to_die = CYCLE_TO_DIE;
	if (parse_args(&vm, argc, argv) &&
		create_player(&vm) &&
		create_cursors(&vm))
	{
		if (vm.v && !vm.dump && !vm.d)
			init_ncurses();
		introduce_players(&vm);
		game_cycle(&vm);
	}
	free_all(&vm);
	return (0);
}
